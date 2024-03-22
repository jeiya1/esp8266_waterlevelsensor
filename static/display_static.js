function updateScaledValues() {
    fetch("http://127.0.0.1:5000/get_data")
        .then(response => response.json())
        .then(data => {
            const scaledDisplay = document.getElementById("scaledDisplay");
            if (data.length > 0) {
                const latestData = data[data.length - 1];
                const scaledValue = ((latestData.data - 12852745 ) / (14473775 - 12852745)) * 100;

                let color;
                if (scaledValue <= 20) {
                    color = "green";
                } else if (scaledValue <= 60) {
                    color = "rgb(220,220,0)";
                } else if (scaledValue <= 90) {
                    color = "orange";
                } else {
                    color = "red";
                }

                const scaledText = `Scaled Value: ${scaledValue.toFixed(2)}%`;
                scaledDisplay.textContent = scaledText;
                scaledDisplay.style.color = color;
            } else {
                scaledDisplay.textContent = "No data received yet";
            }
        })
        .catch(error => {
            const scaledDisplay = document.getElementById("scaledDisplay");
            scaledDisplay.textContent = `Error fetching data: ${error.message}`;
        });
}

updateScaledValues();
setInterval(updateScaledValues, 5000);
