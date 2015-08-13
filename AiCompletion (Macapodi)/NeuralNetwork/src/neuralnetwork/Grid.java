package neuralnetwork;

//package comps;

import javax.swing.JPanel;

public class Grid extends JPanel{
 public final static int ROWS = 15;
 public final static int COLUMNS = 15;
 private static double [] bits; 
 private static Tile [][] grid;
 public static boolean mouseDragged;
 public static Object mouseLock = new Object();
 
 public Grid(){
  setLayout(null);
  setBounds(0, 0, ROWS*Tile.TILE_SIDE, COLUMNS*Tile.TILE_SIDE);
  mouseDragged = false;
  grid = new Tile [ROWS][COLUMNS];
  bits = new double [ROWS*COLUMNS];
  
  for (int i = 0; i < ROWS; i++){
   for (int j = 0; j < COLUMNS; j++){
    grid[i][j] = new Tile(j, i);
    bits[j + (COLUMNS * i)] = 0;
    add(grid[i][j]); //Place tile on grid
   }
  }
 }
 public static void setBit(int i, int j, int x){
  bits[j + (COLUMNS * i)] = x;
 }
 /**
  * Reset the grid to white tiles only.
  */ 
 public void reset(){
  for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLUMNS; j++){
                grid[i][j].setActive(false);
                bits[j + (COLUMNS * i)] = 0;
            }
        }
 }
 /**
  * Returns a linear array of the inputs
  */
 public double [] getArray(){
    bits[0] = 1.0;
  for (int i = 1; i < ROWS; i++){
            for (int j = 1; j < COLUMNS; j++){
                if (grid[i][j].active)
                 bits [j + (COLUMNS * i)] = 1.0;
                else bits [j + (COLUMNS * i)] = 0.0;
            }
        }
  return bits;
 }
 
}
