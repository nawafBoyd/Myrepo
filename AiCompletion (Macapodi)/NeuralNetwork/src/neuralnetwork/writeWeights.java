/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetwork;

import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.util.Formatter;
import java.util.Random;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author nawaf
 */
public class writeWeights {
  private static  double[][] inputlayer_wights =new double[193][331];
  private   static       double[][] hiddenlayer_wights=new double[3][194];
    public static void main(String [] args){
        try {
            // TODO code application logic here
            
            
            File file = new File("weights.txt");
            Scanner scanner = new Scanner(file);
            
            for(int i=0;i<193;i++){
                for(int j=0;j<331;j++){
                    String next=scanner.next();
                    inputlayer_wights[i][j]=Double.parseDouble(next);
                    
                }
                //System.out.print("\n");
            }
            
            
            //String de=scanner.next();
            for(int i=0;i<3;i++){
                for(int j=0;j<194;j++){
                    String next=scanner.next();
                    hiddenlayer_wights[i][j]=Double.parseDouble(next);
                    
                }
               // System.out.print("\n");
            }
            
            //System.out.println(doubs2[193][2]);
            
        } catch (FileNotFoundException ex) {
            //Logger.getLogger(Neural.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        
        try {
            int thei=0;
            int thej=0;
            Random doub=new Random();
            FileWriter outStream = new FileWriter("weigths.txt");
            for(int j=0;j<100;j++){
            for(int i=0; i<226;i++){
                
                //outStream.write(String.valueOf(doub.nextDouble())+"\t");
                
                outStream.write(String.valueOf(inputlayer_wights[j][i])+"\t");
                
            }
            outStream.write("\n");
            
            thej++;
            
            }
            
            System.out.print(thej);
            outStream.close();
            
            //write weigths for hidden layer
            FileWriter outStream2 = new FileWriter("hidden.txt");
            for(int j=0;j<3;j++){
            for(int i=0; i<101;i++){
                
                //outStream2.write(String.valueOf(doub.nextDouble())+"\t");
                outStream2.write(String.valueOf(hiddenlayer_wights[j][i])+"\t");
                
            }
            outStream2.write("\n");
            
            
            
            }
            
            
            outStream2.close();
            
            
        } catch (IOException ex) {
            Logger.getLogger(writeWeights.class.getName()).log(Level.SEVERE, null, ex);
        }



    }
 
}
