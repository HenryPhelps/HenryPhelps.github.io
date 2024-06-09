document.addEventListener('DOMContentLoaded', function() {
    const button = document.createElement('button');
    button.textContent = 'Click me!';
    const mainText = document.getElementById("main-text");
    const originalText = mainText.textContent;
    const newText = "<3";
    const mainSection = document.querySelector('main p');
    button.addEventListener('click', function() {
        alert("I LOVE YOU!");
        if (mainText.textContent === originalText) {
            mainSection.style.fontSize = "60px";
            mainSection.style.color = "#eb0dd8";
            mainText.textContent = newText;
        } else {
            mainSection.style.fontSize = "30px";
            mainSection.style.color = "white";
            mainText.textContent = originalText;
        }
    });
    const buttonContainer = document.querySelector('.button-container');
    buttonContainer.appendChild(button);
});