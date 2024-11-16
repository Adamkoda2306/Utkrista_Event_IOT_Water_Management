import 'package:flutter/material.dart';
import '../model/devices.dart';

class SecondaryPage extends StatelessWidget {
  final List<Device> devices;

  SecondaryPage({required this.devices});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Center(child: const Text('All Devices List')),
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
        child: ListView.builder(
          itemCount: devices.length,
          itemBuilder: (context, index) {
            final device = devices[index];
            return Card(
              margin: EdgeInsets.symmetric(vertical: 10),
              color: _getCardColor(device.level),
              elevation: 5,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(10),
              ),
              child: Padding(
                padding: const EdgeInsets.all(15),
                child: ListTile(
                  title: Center(
                    child: Text(
                      device.areaName,
                      style:
                          TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
                    ),
                  ),
                  subtitle: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      _buildDeviceDetailRow(
                          Icons.water_drop, 'pH: ${device.ph}'),
                      _buildDeviceDetailRow(
                          Icons.opacity, 'Turbidity: ${device.turbidity}'),
                      _buildDeviceDetailRow(Icons.air, 'DO: ${device.doValue}'),
                      _buildDeviceDetailRow(Icons.thermostat,
                          'Temperature: ${device.temperature}°C'),
                      _buildDeviceDetailRow(Icons.settings_input_antenna,
                          'Conductivity: ${device.conductivity} µS/cm'),
                    ],
                  ),
                ),
              ),
            );
          },
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
        Text(text, style: TextStyle(fontSize: 16)),
      ],
    );
  }
}
