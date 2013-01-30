/**
 * Shared Drawing Canvas (Client) 
 * by Alexander R. Galloway. 
 * 
 * The Processing Client class is instantiated by specifying a remote 
 * address and port number to which the socket connection should be made. 
 * Once the connection is made, the client may read (or write) data to the server.
 * Before running this program, start the Shared Drawing Canvas (Server) program.
 */


import processing.net.*;

Client c;
String input;
float data[];

void setup() 
{
  size(450, 255);
  background(204);
  stroke(0);
  frameRate(5); // Slow it down a little 127.0.0.1
  // Connect to the server's IP address and port
  c = new Client(this, "192.168.2.21", 12345); // Replace with your server's IP and port
}

void draw() 
{
  background(204);
  if (mousePressed == true) {
    // Draw our line
    stroke(255);
    line(pmouseX, pmouseY, mouseX, mouseY);
    // Send mouse coords to other person
    c.write(pmouseX + " " + pmouseY + " " + mouseX + " " + mouseY + "\n");
  }
  
  // Receive data from server
  if (c.available() > 0) {
    input = c.readString();
    input = input.substring(0, input.indexOf("\n")); // Only up to the newline
    data = float(split(input, ' ')); // Split values into an array
    // Draw line using received coords
    //println("x: " + data[0] + " y: " + data[1]);
    fill(data[2]);
    ellipse(width/2 + width/2 *data[1], height/2 + height/2 * data[0], 15, 15);
    fill(data[5]);
    ellipse(width/2 + width/2 *data[4], height/2 + height/2 * data[3], 15, 15);
    //line(width/2, height/2, width/2 + width/2 *data[1], height/2 + height/2 * data[0]);
  }
  if (key == 'q')
  {
    c.stop();
    //exit();
  }
}
