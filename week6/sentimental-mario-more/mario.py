import cs50


# Function to Get height for half pyramid
def ask_height():
    while True:
        height = cs50.get_int("Height: ")
        if height > 0 and height < 9:
            return height
        else:
            print("Input an Integer between 1 and 8.")


# Function to Create Pyramid
def pyramid(height):
    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i + "  " + "#" * i)


# prompt Height
height = ask_height()

# Create Pyramid
pyramid(height)
