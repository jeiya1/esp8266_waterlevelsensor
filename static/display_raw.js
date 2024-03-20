function updateMessage() {
    fetch("http://127.0.0.1:5000/get_data")
        .then(response => response.json())
        .then(data => {
            const messageDisplay = document.getElementById("messageDisplay");
            if (data.length > 0) {
                const latestMessage = data[data.length - 1];
                const messageText = `Latest Data: ${latestMessage.data}`;
                messageDisplay.textContent = messageText;
            } else {
                messageDisplay.textContent = "No data received yet";
            }
        })
        .catch(error => {
            const messageDisplay = document.getElementById("messageDisplay");
            messageDisplay.textContent = `Error fetching data: ${error.message}`;
        });
}

updateMessage();
setInterval(updateMessage, 5000);
