/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neural;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.JTextArea;

/**
 *
 * @author Acer
 */
public class weigths {
    String words="";
    public void readTextFile(JTextArea display, String fileName) {
 try {
  BufferedReader inStream                          // Create and open the stream
      = new BufferedReader (new FileReader(fileName));
  String line = inStream.readLine();               // Read one line
  while (line != null) {                           // While more text
      words=words+line+"\n";
      display.append(line + "\n");                 // Display a line
      line = inStream.readLine();                  // Read next line
  }
   inStream.close();                               // Close the stream
  } catch (FileNotFoundException e) {
   display.setText("IOERROR: "+ fileName +"  NOT  found\n");
   e.printStackTrace();
  } catch ( IOException e ) {
   display.setText("IOERROR:"  + e.getMessage() + "\n");
   e.printStackTrace();
  }
}              
}
