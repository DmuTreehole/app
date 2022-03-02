import 'dart:io';
import 'dart:convert';

main() {

  var DESTINATION_ADDRESS=InternetAddress("192.168.1.255");

  RawDatagramSocket.bind(InternetAddress.anyIPv4, 8889).then((RawDatagramSocket udpSocket) {
    udpSocket.broadcastEnabled = true;
    List<int> data =utf8.encode('TEST\n');
    udpSocket.send(data, DESTINATION_ADDRESS, 7895);
 });

}
