

import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';

void main() {
  runApp(const ControlMenu());
}
class ControlMenu extends StatelessWidget {
  const ControlMenu({ Key? key }) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold
      (
        appBar: AppBar(
          centerTitle: true,
          title: const Text('Control Menu'),
        ),
        body: Column(
          children:<Widget> [
              Expanded(
              child:                
              TextField(
                textAlign:TextAlign.center ,
                decoration: InputDecoration(
                  icon: Icon(Icons.person),
                  labelText: "IP地址",
                ),
              )
            ),
              Expanded(
              child:
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children:<Widget> [
                  FloatingActionButton(
                  child: Text("Up"),
                  onPressed: null,
                    )
                ]
              )
              ),
              Expanded(
              child:
              Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                children:<Widget> [
                  FloatingActionButton(
                  child: Text("Left"),
                  onPressed: null,
                    ),
                  FloatingActionButton(
                  child: Text("Right"),
                  onPressed: null,
                    )
                ]
              )
              ),
              Expanded(
              child:
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children:<Widget> [
                  FloatingActionButton(
                  child: Text("Down"),
                  onPressed: null,
                    )
                ]
              )
              ),
        ],
        )
      ),
    );
  }
}