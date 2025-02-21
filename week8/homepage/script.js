function showProjectDetails(project) {
    alert(`You clicked on ${project}! This is a JavaScript alert.`);
}

document


// Function to show an alert when the contact form is submitted
function showAlert() {
    alert("Thank you for contacting us! We will get back to you soon.");
}

// Add event listener to the contact form submit button
document.getElementById("contactForm").addEventListener("submit", function(event) {
    event.preventDefault();  // Prevent form submission for demonstration
    showAlert();
});

// Example of a function that changes the background color of the page when a button is clicked
function changeBackgroundColor() {
    document.body.style.backgroundColor = "#f0f8ff";  // Change background to a light color
}

// Add event listener to a button with ID 'colorChangeButton'
document.getElementById("colorChangeButton").addEventListener("click", changeBackgroundColor);

// Example function to toggle a class on a specific element (like hiding/showing an element)
function toggleVisibility() {
    const element = document.getElementById("toggleElement");
    element.classList.toggle("hidden");
}

// Add event listener to a button that will toggle visibility of an element
document.getElementById("toggleButton").addEventListener("click", toggleVisibility);
