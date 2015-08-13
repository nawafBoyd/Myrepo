/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetwork;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author nawaf
 */
public class read {
    public static double[][] weights=new double[100][226];
    public static double[][] hidden_weights=new double[3][101];
    public static void main(String args[]){
       File file = new File("weigths.txt");
       
        try {
            Scanner scanner = new Scanner(file);
            for(int i=0;i<100;i++){
                
                for(int j=0;j<226;j++){
                    String next = scanner.next();
                    weights[i][j]=Double.parseDouble(next);
                }
            }
            System.out.print(weights[99][225]+"\n\n");
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(read.class.getName()).log(Level.SEVERE, null, ex);
        }
        //for hidden layer
        File file2 = new File("hidden.txt");
        try {
            Scanner scanner = new Scanner(file2);
            for(int i=0;i<3;i++){
                
                for(int j=0;j<101;j++){
                    String next = scanner.next();
                    hidden_weights[i][j]=Double.parseDouble(next);
                }
            }
            System.out.print(hidden_weights[2][100]);
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(read.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
