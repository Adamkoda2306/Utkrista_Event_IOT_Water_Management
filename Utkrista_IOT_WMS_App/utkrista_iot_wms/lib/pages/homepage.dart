import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';
import '../model/devices.dart';
import 'secondpage.dart';

class Homepage extends StatefulWidget {
  const Homepage({super.key});

  @override
  State<Homepage> createState() => _HomepageState();
}

class _HomepageState extends State<Homepage> {
  final DatabaseReference _databaseRef =
      FirebaseDatabase.instance.ref('Utkrista_IOT/Devices');

  List<Device> devices = [];

  @override
  void initState() {
    super.initState();
    _fetchData();
  }

  void _fetchData() {
    _databaseRef.onValue.listen((event) {
      final data = event.snapshot.value as Map<dynamic, dynamic>?;
      if (data != null) {
        final List<Device> loadedDevices = [];
        data.forEach((key, value) {
          try {
            loadedDevices.add(Device.fromMap(value));
          } catch (e) {
            print('Error parsing device data: $e');
          }
        });

        setState(() {
          devices = loadedDevices;
        });
      } else {
        print('No data found in Firebase');
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Center(
          child: const Text(
            'Water Management System',
            textAlign: TextAlign.center,
          ),
        ),
        backgroundColor: Colors.transparent,
        elevation: 0,
        flexibleSpace: Container(
          decoration: BoxDecoration(
            gradient: LinearGradient(
              colors: [Colors.blue.shade400, Colors.blue.shade700],
              begin: Alignment.topLeft,
              end: Alignment.bottomRight,
            ),
          ),
        ),
        foregroundColor: Colors.white,
      ),
      body: Container(
        decoration: BoxDecoration(
          gradient: LinearGradient(
            colors: [Colors.blue.shade400, Colors.blue.shade700],
            begin: Alignment.topLeft,
            end: Alignment.bottomRight,
          ),
        ),
        padding: const EdgeInsets.all(15),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            // Replace Lottie animation with an image
            Container(
              height: 300,
              child: Image.asset(
                'assets/images/water.png',
                fit: BoxFit.contain, // Adjust image scaling if needed
              ),
            ),

            // Display the first device's details or a placeholder
            devices.isNotEmpty
                ? Card(
                    margin: EdgeInsets.symmetric(vertical: 10),
                    color: _getCardColor(devices[0].level),
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(15),
                    ),
                    elevation: 10,
                    child: Padding(
                      padding: EdgeInsets.all(20),
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          Center(
                            child: Text(
                              devices[0].areaName,
                              style: TextStyle(
                                fontSize: 22,
                                fontWeight: FontWeight.bold,
                                color: Colors.black,
                              ),
                            ),
                          ),
                          SizedBox(height: 10),
                          _buildDeviceDetailRow(
                              Icons.water_drop, 'pH: ${devices[0].ph}'),
                          _buildDeviceDetailRow(Icons.opacity,
                              'Turbidity: ${devices[0].turbidity}'),
                          _buildDeviceDetailRow(
                              Icons.air, 'DO: ${devices[0].doValue}'),
                          _buildDeviceDetailRow(Icons.thermostat,
                              'Temperature: ${devices[0].temperature}°C'),
                          _buildDeviceDetailRow(Icons.settings_input_antenna,
                              'Conductivity: ${devices[0].conductivity} µS/cm'),
                        ],
                      ),
                    ),
                  )
                : const Center(child: Text('No device data available')),

            SizedBox(height: 50),

            // Button to navigate to the secondary page to view all devices
            Center(
              child: ElevatedButton(
                onPressed: () async {
                  final selectedDevice = await Navigator.push<Device?>(
                    context,
                    MaterialPageRoute(
                      builder: (context) => SecondaryPage(devices: devices),
                    ),
                  );

                  // If a device is selected, update the displayed device
                  if (selectedDevice != null) {
                    setState(() {
                      // Replace the first device with the selected device
                      devices[0] = selectedDevice;
                    });
                  }
                },
                child: const Text('View All Devices'),
                style: ElevatedButton.styleFrom(
                  backgroundColor: Colors.blue[100],
                  padding: EdgeInsets.symmetric(horizontal: 20, vertical: 12),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(8),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Color _getCardColor(String level) {
    if (level == 'Safe') {
      return Colors.green.shade200;
    } else if (level == 'Warning') {
      return Colors.yellow.shade200;
    } else {
      return Colors.red.shade200;
    }
  }

  Widget _buildDeviceDetailRow(IconData icon, String text) {
    return Row(
      children: [
        Icon(icon, size: 20, color: Colors.blue),
        SizedBox(width: 10),
        Text(text, style: TextStyle(fontSize: 18)),
      ],
    );
  }
}
