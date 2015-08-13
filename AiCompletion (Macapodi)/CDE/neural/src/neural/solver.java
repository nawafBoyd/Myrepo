/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neural;

import java.io.DataInputStream;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author mcpd
 */
public class solver {
    
    public double[] output;
     ArrayList<String> config;
        ArrayList<String> config2;
        String[][] firstTable=new String[331][194];
         String[][] secondTable=new String[3][194];
    public solver(){
        output=new double[3];
        this.getweights();
        this.getTable2();
        this.chop();
        this.chop2();
    }
    
    public void solve(double[] A){
        try{
     double a= 0.0;
     
     double[] b =new double[193];
     for(int i=0;i<193;i++){
         for( int sec=0;sec<331;sec++){
             double ft=Double.parseDouble(this.firstTable[sec][i]);
             a=a+(A[sec]*ft);
         }
         b[i]=g(a);
         a=0.0;
     }
     double o=0.0;
     for(int l=0;l<3;l++){
         for(int i=0;i<194;i++){
             double st=Double.parseDouble(this.secondTable[l][i]);
             o=o+(b[i]*st);
         }
         this.output[l]=g(o);
         o=0.0;
         
     }
     }catch(Exception e){
      System.out.print("the script"+e);      
     }
   
     
     
    }
    private double g(double X){
        double x=(-1)*X;
        
        return 1/(1+Math.exp(x));
    }
    private void getweights(){
            try {
            File file = null;
            
            try {
                file = new File("weights.txt");
                //file = new File("table2.txt");
                //InputStream res = this.getClass().getResourceAsStream("/icons/address.txt");
                //res.toString();
            } catch (Exception ex) {
                System.out.print(ex);
            }
         
         
         StringBuilder fileContents = new StringBuilder((int)file.length());
         Scanner scanner = new Scanner(file);
         String lineSeparator = System.getProperty("line.separator");
          config=new ArrayList<String>();
         String b="localhost";
         
         try {
             while(scanner.hasNext()) {        
                 b=scanner.next();
                 config.add(b);
                 
             }
             chop();
             
         } finally {
             scanner.close();
             System.out.print(config.size());
             
         }
        } catch (FileNotFoundException ex) {
                System.out.print(ex);                                                                                       
        }
        }
        
        
        
        private void chop(){
            
        try{  
        int index=0;
        for(int i=0;i<193;i++)
        {
         for(int sec=0;sec<331;sec++)
         {
             
            firstTable[i][sec]=config.get(index++);
         }
        }
        
        }catch(Exception e){
            
        }
        
            System.out.println(firstTable[0][330]);
            
             
        }
        private void getTable2(){
            try {
            File file = null;
            
            try {
                //file = new File("weights.txt");
                file = new File("table2.txt");
                
            } catch (Exception ex) {
                System.out.print(ex);
            }
         
         
         
         Scanner scanner = new Scanner(file);
         
          config2=new ArrayList<String>();
         String b="localhost";
         
         try {
             while(scanner.hasNext()) {        
                 b=scanner.next();
                 config2.add(b);
                 
             }
            // chop();
             chop2();
             
         } finally {
             scanner.close();
             System.out.println(config2.get(194));
             
         }
        } catch (FileNotFoundException ex) {
                System.out.print(ex);                                                                                       
        }
            
        }
        private void chop2(){
            
            
        int index=0;
        for(int i=0;i<3;i++)
        {
         for(int sec=0;sec<194;sec++)
         {
             
            secondTable[i][sec]=config2.get(index++);
         }
        }
        
        
        
            System.out.print(secondTable[0][193]);
             
        }
    
}
