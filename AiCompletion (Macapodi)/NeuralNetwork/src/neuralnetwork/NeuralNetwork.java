/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neuralnetwork;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mcpd
 */
public class NeuralNetwork {

    /**
     * @param args the command line arguments
     */
    private double[] a_j=new double[101];
    private double[] inj=new double[101];
    private double[] ini=new double[3];
    public  double[][] weights=new double[100][226];
    public  double[][] hidden_weights=new double[3][101];
    
    public double[][] newHidden_L=new double[3][101];
    public  double[][] newWeights=new double[100][226];
    public double[] c=new double[3];
    private double[] D_O=new double[]{1.0,1.3,1.2};
    private double alpha=0.5;
    private double[] Delta=new double[3];
    private double[] Delta_2=new double[101];
    public void read_Weights(){
        
        File file = new File("weigths.txt");
       
        try {
            Scanner scanner = new Scanner(file);
            for(int i=0;i<100;i++){
                
                for(int j=0;j<226;j++){
                    String next = scanner.next();
                    double pd = Double.parseDouble(next);
                    weights[i][j]=pd;
                }
            }
            System.out.print("wets"+weights[99][225]+"\n\n");
            
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
            //System.out.print(hidden_weights[2][100]);
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(read.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void write_Weights(){
        try {
            int thei=0;
            int thej=0;
            Random doub=new Random();
            //doub.setSeed(thej);
            FileWriter outStream = new FileWriter("weigths.txt");
            for(int j=0;j<100;j++){
            for(int i=0; i<226;i++){
                
                outStream.write(String.valueOf(doub.nextFloat())+"\t");
                
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
                
                outStream2.write(String.valueOf(doub.nextFloat())+"\t");
                
            }
            outStream2.write("\n");
            
            
            
            }
            
            
            outStream2.close();
            
            
        } catch (IOException ex) {
            Logger.getLogger(writeWeights.class.getName()).log(Level.SEVERE, null, ex);
        }

    }
    public void solve(double[] array){
        this.read_Weights();
        double[] input_layer=add(array.clone()); 
        double[] z=new double[100]; //for output layer
        double temp=0;
        
     for(int h=0;h<100;h++){
     for(int j=0;j<226;j++){
         
         //System.out.print(this.inputlayer_wights[h][j+1]+"\n");
        temp=this.weights[h][j]*input_layer[j]+temp;
        
        
     }
    // System.out.print("g(temp)= "+g(temp)+"\n");
     
     this.inj[h]=temp;
     z[h]=g(temp);
     //System.out.print("g(temp)= "+g(temp)+"\n");
     temp=0;
     
     }
     /////////////
     double[] hidden_layer=add(z);
     this.a_j=hidden_layer.clone();
     
     
     double[] dc=new double[3]; //for output layer
     
     double temp1=0;
     
     for(int h=0;h<3;h++){
     for(int j=0;j<101;j++){
         
         
        temp1=this.hidden_weights[h][j]*hidden_layer[j]+temp1;
     }
     dc[h]=g(temp1);
     System.out.println("temp1="+temp1);
     System.out.println(g(temp1));
     this.ini[h]=temp1;
     
     temp1=0;
     
     }
     //dc[0]=s(dc[0]);
    //dc[1]=s(dc[1]);
     //dc[2]=s(dc[2]);
     
     //c[0]=trim(dc[0]);
     //c[1]=trim(dc[1]);
     //c[2]=trim(dc[2]);
     c[0]=dc[0];
     c[1]=dc[1];
     c[2]=dc[2];
    }
    private double trim(double d){
        if(d<0){
            return 0;
        }
        else if(d>1){
            return 1;
        }
        else
            return d;
    }
    private double[] add(double[] arr){
        double[] final_array=new double[arr.length+1];
        final_array[0]=1.0;
        for(int i=1;i<final_array.length;i++){
            final_array[i]=arr[i-1];
        }
        return final_array;
    }
    private double g(double X){
        double x=(-1.0)*X;
        double e=2.718;
        double w=Math.pow(e, x);
        double pow = 1.0+w;
        double ww=1.0/pow;
        //System.out.println("g--"+ww);
        
        return ww;
    }
    private double s(double x){
        return (x-0.1)/0.8;
    }
    private double Err(double y,double o){
        
        
        return (y-o);
    }
    private double g_dr(double x){
        double ge=g(x);
        //System.out.println("ge="+ge);
        double temp=1-ge;
        return temp*ge;
    }
    private void delta(){
        double[] ret=new double[3];
        for(int i=0;i<3;i++){
            ret[i]=Err(this.D_O[i],this.c[i])*g_dr(this.ini[i]);
        }
        this.Delta=ret.clone();
    }
    
    private void delta_2(){
        double[] ret=new double[101];
        for(int j=0;j<101;j++){
            double temp=g_dr(this.inj[j]);
            double temp2=0;
            for(int i=0;i<3;i++){
               temp2=temp2+this.hidden_weights[i][j]*this.Delta[i]; 
            }
            this.Delta_2[j]=temp*temp2;
            temp=0;
        }
        
    }
    
    public void train(double[] array){
        //this.write_Weights();
      double[] array_clone=add(array.clone());
      //do{
      delta();
      delta_2();
      for(int i=0;i<3;i++){
          for(int j=0;j<101;j++){
              double temp=this.Delta[i]*this.a_j[j];
              double temp2=temp*this.alpha;
              
              
              this.newHidden_L[i][j]=temp2+this.hidden_weights[i][j];
              
          }
      }
      try{
      for(int j=0;j<101;j++){
          for(int k=0;k<226;k++){
              double temp=this.Delta_2[j]*array_clone[k];
              double temp2=temp*this.alpha;
              
              this.newWeights[j][k]=this.weights[j][k]+temp2;
              
          }
      }
      //this.solve(array);
      }
      catch (Exception e){
          
      }
     
      //}while (!isConverge());
      
   
    }
    private boolean isConverge(){
        if(this.c[0]<=this.D_O[0] && this.c[1]<=this.D_O[1] && this.c[2]<=this.D_O[2])
            return true;
        else
            return false;
    }
    
    public void write_new_Weights(){
        try {
            
            Random doub=new Random();
            FileWriter outStream = new FileWriter("weigths.txt");
            for(int j=0;j<100;j++){
            for(int i=0; i<226;i++){
                
                outStream.write(this.newWeights[j][i]+"\t");
                
            }
            outStream.write("\n");
            
            
            
            }
            
            
            outStream.close();
            
            //write weigths for hidden layer
            FileWriter outStream2 = new FileWriter("hidden.txt");
            for(int j=0;j<3;j++){
            for(int i=0; i<101;i++){
                
                outStream2.write(this.newHidden_L[j][i]+"\t");
                
            }
            outStream2.write("\n");
            
            
            
            }
            
            
            outStream2.close();
            
            
        } catch (IOException ex) {
            Logger.getLogger(writeWeights.class.getName()).log(Level.SEVERE, null, ex);
        }

        
        
    }
    
    
    public static void main(String[] args) {
        // TODO code application logic here
    }
}
