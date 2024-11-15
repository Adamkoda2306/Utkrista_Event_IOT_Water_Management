// Import Firebase modules
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.0.0/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/9.0.0/firebase-database.js";

// Firebase configuration
const firebaseConfig = {
    apiKey: "AIzaSyC-6MWzxf_WAUupiJASmkb4mkQTZjJdWWc",
    authDomain: "es-lab-be4bb.firebaseapp.com",
    databaseURL: "https://es-lab-be4bb-default-rtdb.firebaseio.com",
    projectId: "es-lab-be4bb",
    storageBucket: "es-lab-be4bb.appspot.com",
    messagingSenderId: "1234567890",
    appId: "1:1234567890:web:abcdefghij"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const database = getDatabase(app);

// Helper to set status class based on value
function getStatusClass(value, type) {
    if (type === "Ph") {
        if (value >= 6.5 && value <= 8.5) return "safe";
        if ((value >= 5 && value < 6.5) || (value > 8.5 && value <= 9)) return "warning";
        return "unsafe";
    }
    if (type === "Turbidity") {
        if (value < 5) return "safe";
        if (value >= 5 && value <= 10) return "warning";
        return "unsafe";
    }
    if (type === "Temperature") {
        if (value >= 5 && value <= 25) return "safe";
        if (value > 25 && value <= 30) return "warning";
        return "unsafe";
    }
    if (type === "DO") {
        if (value > 6) return "safe";
        if (value >= 4 && value <= 6) return "warning";
        return "unsafe";
    }
    if (type === "Conductivity") {
        if (value < 1500) return "safe";
        if (value >= 1500 && value <= 4000) return "warning";
        return "unsafe";
    }
}

// Fetch data and update the page
function fetchData() {
    const deviceContainer = document.getElementById("deviceContainer");
    const devicesRef = ref(database, "/Utkrista_IOT/Devices");

    onValue(devicesRef, (snapshot) => {
        deviceContainer.innerHTML = ""; // Clear the container
        const devices = snapshot.val();

        if (devices) {
            Object.entries(devices).forEach(([deviceKey, deviceData]) => {
                const areaName = deviceData.AreaName || "Unknown Area";

                // Create a div for each device
                const deviceDiv = document.createElement("div");
                deviceDiv.classList.add("device");

                // Populate the div with sensor values and their status
                deviceDiv.innerHTML = `
                    <h3>${areaName}</h3>
                    <div><strong>pH Level:</strong> <span class="${getStatusClass(deviceData.Sensorvalues.Ph, 'Ph')}">${deviceData.Sensorvalues.Ph || "N/A"}</span></div>
                    <div><strong>Turbidity (NTU):</strong> <span class="${getStatusClass(deviceData.Sensorvalues.Turbidity, 'Turbidity')}">${deviceData.Sensorvalues.Turbidity || "N/A"}</span></div>
                    <div><strong>Dissolved Oxygen (mg/L):</strong> <span class="${getStatusClass(deviceData.Sensorvalues.DO, 'DO')}">${deviceData.Sensorvalues.DO || "N/A"}</span></div>
                    <div><strong>Temperature (°C):</strong> <span class="${getStatusClass(deviceData.Sensorvalues.Temperature, 'Temperature')}">${deviceData.Sensorvalues.Temperature || "N/A"}</span></div>
                    <div><strong>Conductivity (µS/cm):</strong> <span class="${getStatusClass(deviceData.Sensorvalues.Conductivity, 'Conductivity')}">${deviceData.Sensorvalues.Conductivity || "N/A"}</span></div>
                `;

                // Append to the container
                deviceContainer.appendChild(deviceDiv);
            });
        } else {
            deviceContainer.innerHTML = "<p>No devices available.</p>";
        }
    });
}

// Fetch data initially
fetchData();
