package neuralnetwork;

//package comps;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JOptionPane;

public class Window {
 
 private String title;
 private Grid gridPane;
// private MessagePane msgPane;
 private JFrame main;
 private JPanel bPane;
 private JButton done;
 private JButton clear;
 private JButton exit;
 private JButton train;
// private NeuralNet nn;
 private JTextField txt_input;
 private NeuralNetwork nn;
 private message msg;
 //private NeuralNet nn;
 
 public Window(){
  gridPane = new Grid();
 // msgPane = new MessagePane();
  paintFrame();
  paintButtonPane();
  main.add(bPane);
  //main.add(msgPane);
  main.add(gridPane);
  main.setVisible(true);
 // nn = new NeuralNet();
  nn=new NeuralNetwork();
  nn.read_Weights();
  msg=new message(main,true);
 }
 
 private void paintFrame(){
  main = new JFrame();
  main.setResizable(false);
  main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  main.setMinimumSize(new Dimension(480, 400));
  main.setTitle("Pattern Recognizer");
  main.pack();
  main.requestFocusInWindow();
 }

 
 private void paintButtonPane(){
  bPane = new JPanel();
  FlowLayout l = new FlowLayout();
  bPane.setLayout(null);
  l.setAlignment(FlowLayout.LEFT);
  
   //txt_input = new JTextField("", 4);
  //txt_input.setSize(80, 25);
  
  done = new JButton("Recognize");
  clear = new JButton("Clear");
  exit = new JButton("Exit");
  train = new JButton("Train");
  
  //set button sizes and position in the button panel
  done.setBounds(10, 10, 100, 25);
  train.setBounds(120, 10, 100, 25);
  clear.setBounds(230, 10, 100, 25);
  exit.setBounds(340, 10, 100, 25);
  
  done.addActionListener(new ActionListener(){
    @Override
    public void actionPerformed(ActionEvent e){
      //nn.initInputs(gridPane.getArray());
      //nn.forwardPropagation();
     // msgPane.printOutput(nn.getOutput());
        nn.solve(gridPane.getArray());
        msg.show(nn.c[0], nn.c[1], nn.c[2]);
    }
  });
  
  clear.addActionListener(new ActionListener(){
   @Override
   public void actionPerformed(ActionEvent e){
       //nn.write_Weights();
     gridPane.reset();
     main.repaint();
     //msgPane.refreshMessage();
     int i=gridPane.getArray().length;
     System.out.print(i);
   }
  });
  
  exit.addActionListener(new ActionListener(){
   @Override
   public void actionPerformed(ActionEvent e){
    System.exit(0);
   }
  });
  
  train.addActionListener(new ActionListener(){
   @Override
   public void actionPerformed(ActionEvent e){
      nn.write_Weights();
	  //nn.writeWeightsToFile();
      nn.train(gridPane.getArray());
       //nn.write_Weights();
   }
  });
  //train.setEnabled(false);
  
  bPane.add(done);
  bPane.add(clear);
  bPane.add(train);
  bPane.add(exit);
  
  bPane.setBounds(0, 300, 480, 50);
 }
 
 public static void main(String [] args){
  new Window();
 }
 
}
