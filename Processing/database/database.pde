import de.bezier.data.sql.*; // Permite la conexion con la base de datos
import processing.serial.*;

//VARIABLES
Serial myPort;  // The serial port
String c = "Code";
PFont font;
String code = "Code";
String name = "Name";
float balance = 0.0;

//button 1
float x1 = 100;
float y1 = 230;

//button dimensions
float w = 150;
float h = 80;

//DATABASE
MySQL msql;
String user     = "root"; 
String pass     = "root"; 
String database = "arduino"; 
String table    = "account";
String dbhost = "localhost";

void setup() {  
  size(600, 400);
  background(50);
  stroke(0);
  noFill();

  // List all the available serial ports:
  println(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);  

  //Print on draw dialog
  font = loadFont("AdobeThai-Italic-30.vlw");
  textFont(font);
}

void draw() {
  //button 1
  background(#141415);
  rect(x1, y1, w, h);
  text("Press to fill", x1+15, y1-10, 1);
  fill(#CE9292);
  if (mousePressed) {
    if (mouseX>x1 && mouseX <x1+w && mouseY>y1 && mouseY <y1+h) {
      fill(100);
      text("Fill done", x1+15, y1-10, 1);
    }
  } 

  //Arduino
  while (myPort.available () > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {
      //println(inBuffer);             
      if (inBuffer.length()==12) {
        c = correction(inBuffer);
        println(c); 
        dbQuery(c);
      } 
    }
  } 
  text(code, 100, 40, 1);
  text(name, 100, 94, 1);
  text(balance, 94, 138, 1);  

  //llamar refill y llamar buy
}

String correction(String string) {
  String s = "";
  for (int i = 3; i<string.length (); i++) {
    s += string.charAt(i);
  }
  return s;
}

void dbQuery(String codigo) {
  msql = new MySQL( this, dbhost, database, user, pass ); 
  if ( msql.connect() ) {
    println("connection done");
    msql.query("select * from account  where code='"+codigo+"'");
    //if(q){
    while (msql.next ()) {
      code = msql.getString("code");
      name = msql.getString("name");
      balance = msql.getFloat("balance");
    }
    /*}else{
     println ("ERROR: código inválido");
     }*/
  } else {
    println( "connection failed");
  }
}

void refillTag() {
  //cambiar valor de balance en la base de datos
}

void buy() {
  //verificar balance a ver si se puede comprar
}

