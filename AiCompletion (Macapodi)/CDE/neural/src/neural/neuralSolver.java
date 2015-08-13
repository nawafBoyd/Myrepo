/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package neural;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author mcpd
 */
public class neuralSolver {
            double[][] inputlayer_wights =new double[193][331];
            double[][] hiddenlayer_wights=new double[3][194];
            
            double[][] doubs=new double[331][193];
            double[][] doubs2=new double[194][3];
            public double[] c=new double[3];
            public double[] fc=new double[3];
    public neuralSolver(){
        getWeights();
    }
    
    public void getWeights(){
        try {
            // TODO code application logic here
            
            
            File file = new File("weights.txt");
            Scanner scanner = new Scanner(file);
            
            for(int i=0;i<193;i++){
                for(int j=0;j<331;j++){
                    String next=scanner.next();
                    this.inputlayer_wights[i][j]=Double.parseDouble(next);
                    
                }
                //System.out.print("\n");
            }
            
            
            //String de=scanner.next();
            for(int i=0;i<3;i++){
                for(int j=0;j<194;j++){
                    String next=scanner.next();
                    this.hiddenlayer_wights[i][j]=Double.parseDouble(next);
                    
                }
               // System.out.print("\n");
            }
            
            //System.out.println(doubs2[193][2]);
            
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Neural.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    public void solve(double[] array){
      //System.out.print(this.inputlayer_wights[0][330]);  
        
     double[] input_layer=add(array);  
     
     double[] z=new double[193]; //for output layer
     
     double temp=0;
     
     for(int h=0;h<193;h++){
     for(int j=0;j<331;j++){
         
         //System.out.print(this.inputlayer_wights[h][j+1]+"\n");
        temp=this.inputlayer_wights[h][j]*input_layer[j]+temp;
     }
     z[h]=g(temp);
     temp=0;
     
     }
     
     /////////////
     double[] hidden_layer=add(z);
     
     double[] dc=new double[3]; //for output layer
     
     double temp1=0;
     
     for(int h=0;h<3;h++){
     for(int j=0;j<194;j++){
         
         //System.out.print(this.inputlayer_wights[h][j+1]+"\n");
        temp1=this.hiddenlayer_wights[h][j]*hidden_layer[j]+temp1;
     }
     dc[h]=g(temp1);
     temp1=0;
     
     }
     dc[0]=s(dc[0]);
     dc[1]=s(dc[1]);
     dc[2]=s(dc[2]);
     
     c[0]=trim(dc[0]);
     c[1]=trim(dc[1]);
     c[2]=trim(dc[2]);
     
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
    
    private double s(double x){
        return (x-0.1)/0.8;
    }
    private double g(double X){
        double x=(-1)*X;
       
        double w=1+Math.exp(x);
        return 1/w;
    }
    
    
}
