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
 * @author Acer
 */
public class Neural {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        try {
            // TODO code application logic here
            neuralSolver nn=new neuralSolver();
            System.out.print(nn.inputlayer_wights[1][2]+"\n\n");
            System.out.print(nn.hiddenlayer_wights[1][2]);
            
            
            
            
            
            String[][] ft=new String[194][331];
            String[][] st=new String[194][3];
            double[][] doubs=new double[331][193];
            double[][] doubs2=new double[194][3];
            File file = new File("weights.txt");
            Scanner scanner = new Scanner(file);
            /*
            for(int i=0;i<193;i++){
                for(int j=0;j<331;j++){
                    ft[j][i]=scanner.next();
                }
            }
            System.out.print("[1][-]"+ft[192][330]);
            /*
            for(int i=0;i<193;i++){
                for(int j=0;j<331;j++){
                    doubs[j][i]=Double.parseDouble(ft[j][i]);
                }
            }
            //String de=scanner.next();
            for(int i=0;i<3;i++){
                for(int j=0;j<194;j++){
                    st[j][i]=scanner.next();
                }
            }
            for(int i=0;i<3;i++){
                for(int j=0;j<194;j++){
                    doubs2[j][i]=Double.parseDouble(st[j][i]);
                }
            }
            System.out.println(doubs2[193][2]);
            */
        } catch (FileNotFoundException ex) {
            Logger.getLogger(Neural.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
