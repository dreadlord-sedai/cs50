import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Get users stock holdings grouped by symbol
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id
    )

    portfolio = []
    total_stock_value = 0

    # Get User cash balance **before** the loop
    cash_balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Loop through each stock, get current price and calculate total
    for stock in stocks:
        stock_data = lookup(stock["symbol"])  # Fetch live stock price
        if not stock_data:
            continue  # invalid stock

        current_price = stock_data["price"]
        total_value = stock["total_shares"] * current_price
        total_stock_value += total_value

        # Append stock details to portfolio
        portfolio.append(
            {
                "symbol": stock["symbol"],
                "shares": stock["total_shares"],
                "current_price": usd(current_price),
                "total_stock_value": usd(total_stock_value),
            }
        )

    # Calculate Grand total
    grand_total = cash_balance + total_stock_value

    # Render index page
    return render_template("index.html", portfolio=portfolio, cash=usd(cash_balance), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Check if symbol is provided
        if not symbol:
            return apology("Must provide stock symbol", 400)

         # Lookup the stock
        stock = lookup(symbol.upper())
        if stock is None:
            return apology("invalid stock symbol", 400)

        # Check if no.of stocks is positive
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("shares must be a positive integer", 400)
        except ValueError:
            return apology("shares must be a positive integer", 400)

        # Get users cash balance
        user_id = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Calculate total cost
        stock_price = stock["price"]
        total_cost = shares * stock_price

        # Check if User can afford purchase
        if total_cost > user_cash:
            return apology("Insufficient funds", 400)

        # Record purchase in transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_total) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], shares, stock_price, total_cost)

        # Update user cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # redirect to homepage
        return redirect("/")

    # If method is GET render buy form
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    # Get user transactions
    transactions = db.execute(
        "SELECT symbol, shares, price, timestamp, transaction_total FROM transactions WHERE user_id = ? ORDER BY timestamp DESC",
        user_id,
    )

    return render_template("history.html", transactions=transactions, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Look up stock price."""
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Check if symbol is provided
        if not symbol:
            return apology("Must provide stock symbol")

        # Lookup stock price
        stock = lookup(symbol.upper())

        # If stock not found return apology
        if not stock:
            return apology("Stock not found")

        # Render quoted.html and pass stock data
        return render_template("quoted.html", stock=stock)

    # Render quoted page when user comes to /quote using GET
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reach rout via POST (by submitting form)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if all fields are submitted
        if not username or not password or not confirmation:
            return apology("All fields must be sumbitted", 403)

        # Check if password matches confirmation
        if password != confirmation:
            return apology("Password must match Confirmation", 403)

        # Create Hashed password
        hashed_password = generate_password_hash(password)

        # Add user if dosent already exist
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, hashed_password)
        except ValueError:
            return apology("Username Already Exists")

        # Redirect to login after registration
        return redirect("/login")

     # If method is GET (user just visited the website), render the registration page
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    # Query database for stocks the user owns
    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id,
    )

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Validate symbol
        if not symbol:
            return apology("Must select stock", 400)

        # Validate shares input
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("Shares must be a positive integer", 400)
        except ValueError:
            return apology("Shares must be a positive integer", 400)

         # Check if the user owns the stock and has enough shares
        user_shares = db.execute(
            "SELECT SUM(shares) AS total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
            user_id,
            symbol,
        )

        if not user_shares or user_shares[0]["total_shares"] < shares:
            return apology("Not enough shares", 400)

        # Get the current stock price
        stock = lookup(symbol)
        if stock is None:
            return apology("Invalid stock symbol", 400)

        stock_price = stock["price"]
        total_sale_value = shares * stock_price

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_sale_value, user_id)

        # Record sale in transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transaction_total) VALUES (?, ?, ?, ?, ?)",
            user_id,
            symbol,
            -shares,  # Negative to indicate a sale
            stock_price,
            total_sale_value,
        )

        # Redirect to homepage
        return redirect("/")

    # Render the sell page with stocks user owns
    return render_template("sell.html", stocks=stocks)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Funds for user"""
    user_id = session["user_id"]

    if request.method == "POST":
        # Get user input amount
        amount = request.form.get("amount")

        # Ensure input is valid
        if not amount or not amount.isdigit() or int(amount) <= 0:
            return apology("Invalid amount", 400)

        # Update user cash balance
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)

        return redirect("/")
