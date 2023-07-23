void GPS() {
    while (SerialGPS.available() >0) {
       gps.encode(SerialGPS.read());
    }
    lattitude = (gps.location.lat(), 6);
    longitude  = (gps.location.lng(), 6);
//    Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
//    Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
}
