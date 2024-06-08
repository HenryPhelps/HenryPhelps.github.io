document.addEventListener('DOMContentLoaded', () => {
    const button = document.createElement('button');
    button.textContent = 'Click me!';
    document.body.appendChild(button);

    button.addEventListener('click', () => {
        const mainText = document.querySelector('main p');
        mainText.textContent = 'You clicked the button!';
    });
});