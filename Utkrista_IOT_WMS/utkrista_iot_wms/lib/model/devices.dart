class Device {
  final String id; // Unique identifier for each device
  final String areaName;
  final double ph;
  final double turbidity;
  final double doValue;
  final double temperature;
  final double conductivity;
  String level = ''; // Added to store level (safe, warning, unsafe)

  Device({
    required this.id,
    required this.areaName,
    required this.ph,
    required this.turbidity,
    required this.doValue,
    required this.temperature,
    required this.conductivity,
  });

  factory Device.fromMap(Map<dynamic, dynamic> map) {
    final sensorValues = map['Sensorvalues'] ?? {};

    double parseToDouble(dynamic value) {
      if (value is String) {
        return double.tryParse(value) ?? 0.0;
      } else if (value is num) {
        return value.toDouble();
      }
      return 0.0;
    }

    Device device = Device(
      id: map['Id'] ??
          'UnknownId', // Ensure to get the device's unique identifier
      areaName: map['AreaName'] ?? 'Unknown Area',
      ph: parseToDouble(sensorValues['Ph']),
      turbidity: parseToDouble(sensorValues['Turbidity']),
      doValue: parseToDouble(sensorValues['DO']),
      temperature: parseToDouble(sensorValues['Temperature']),
      conductivity: parseToDouble(sensorValues['Conductivity']),
    );

    // Determine the level based on parameters
    device.level = _getDeviceLevel(device);

    return device;
  }

  // Check device status and set the level
  static String _getDeviceLevel(Device device) {
    // Parameters for status determination
    int isTurbiditySafe =
        device.turbidity < 5 ? 1 : (device.turbidity <= 10 ? 2 : 0);
    int isECSafe =
        device.conductivity < 1500 ? 1 : (device.conductivity <= 4000 ? 2 : 0);
    int isTemperatureSafe =
        (device.temperature >= 5 && device.temperature <= 25)
            ? 1
            : (device.temperature <= 30 ? 2 : 0);
    int isDOSafe = device.doValue > 6
        ? 1
        : (device.doValue >= 4 && device.doValue <= 6 ? 2 : 0);
    int isPhSafe = (device.ph >= 6.5 && device.ph <= 8.5)
        ? 1
        : (device.ph >= 5 && device.ph < 6.5 ||
                device.ph > 8.5 && device.ph <= 9
            ? 2
            : 0);

    // Final determination based on all parameters
    if (isPhSafe == 1 &&
        isDOSafe == 1 &&
        isTemperatureSafe == 1 &&
        isECSafe == 1 &&
        isTurbiditySafe == 1) {
      return 'Safe';
    } else if (isPhSafe == 0 ||
        isDOSafe == 0 ||
        isTemperatureSafe == 0 ||
        isECSafe == 0 ||
        isTurbiditySafe == 0) {
      return 'Unsafe';
    } else {
      return 'Warning';
    }
  }
}
