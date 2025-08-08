// script.js

document.addEventListener("DOMContentLoaded", function () {
    const updateButton = document.getElementById("updateBtn");
    const waterButton = document.getElementById("waterBtn");

    updateButton.addEventListener("click", function () {
        alert("Manual Update Activated");
    });

    waterButton.addEventListener("click", function () {
        alert("Watering plants");
    });
});
