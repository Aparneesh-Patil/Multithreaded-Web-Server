console.log("JavaScript loaded from the C++ server.");

document.addEventListener("DOMContentLoaded", () => {
    const button = document.createElement("button");
    button.textContent = "Test JavaScript";

    button.addEventListener("click", () => {
        alert("This JavaScript file was served by your C++ HTTP server.");
    });

    document.body.appendChild(button);
});