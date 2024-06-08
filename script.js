document.addEventListener('DOMContentLoaded', function() {
    const button = document.createElement('button');
    button.textContent = 'Click me!';
    button.addEventListener('click', function() {
        alert("I LOVE YOU!");
        const mainSection = document.querySelector('main p');
        mainSection.style.fontSize = '50px';
        mainSection.style.color = "#eb0dd8";
        mainSection.textContent = "<3";
    });
    const buttonContainer = document.querySelector('.button-container');
    buttonContainer.appendChild(button);
});