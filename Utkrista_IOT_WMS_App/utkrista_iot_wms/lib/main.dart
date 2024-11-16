import 'package:flutter/material.dart';
import 'package:firebase_core/firebase_core.dart';
import 'pages/homepage.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await Firebase.initializeApp(); // Initialize Firebase
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Water Management System',
      theme: ThemeData(primarySwatch: Colors.blue),
      home: Homepage(),
    );
  }
}
