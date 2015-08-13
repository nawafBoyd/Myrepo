package neuralnetwork;

//package comps;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import javax.swing.BorderFactory;
import javax.swing.JComponent;

public class Tile extends JComponent implements MouseListener, MouseMotionListener{
 public static final int TILE_SIDE = 20;
 private int posX, posY;
 public int left, right, top, bottom; //border pixels
 public boolean active;
 private boolean hover;
 
 public Tile(int x, int y){
  posX = x;
  posY = y;
  left = posX*TILE_SIDE;
  top = posY*TILE_SIDE;
  right = left + TILE_SIDE;
  bottom = top + TILE_SIDE;
  active = false;
  hover = false;
  this.setBounds(left, top, TILE_SIDE, TILE_SIDE);
  this.setBorder(BorderFactory.createLineBorder(Color.black, 1));
  //addMouseMotionListener(this);
  addMouseListener(this);
 }
 
 public void setActive(boolean a){
  synchronized(Grid.mouseLock){
   this.active = a;
   if (active) Grid.setBit(posY, posX, 1);
   else Grid.setBit(posY, posX, 0);
   this.repaint();
  }
  if (active) Grid.setBit (posX, posY, 1);
  else Grid.setBit (posX, posY, 0);
 }
 
 public void hover(boolean h){
  synchronized(Grid.mouseLock){
   this.hover = h;
   this.repaint();
  }
 }
 
 @Override
    protected void paintComponent(Graphics g) {
  
  if (active) g.setColor(Color.red);
  else if (hover) g.setColor(Color.darkGray);
  else g.setColor(Color.white);
  
  g.fillRect(0, 0, TILE_SIDE, TILE_SIDE);
  super.paintComponent(g);
    }

 @Override
 public void mouseClicked(MouseEvent arg0) {
  ;
 }

 @Override
 public void mouseEntered(MouseEvent arg0) {
  if (Grid.mouseDragged)
   setActive(true);
  else hover(true);
  
 }

 @Override
 public void mouseExited(MouseEvent arg0) {
  hover(false);
 }

 @Override
 public void mousePressed(MouseEvent arg0) {
  Grid.mouseDragged =true;
  if (active) setActive(false);
  else setActive(true);
 }

 @Override
 public void mouseReleased(MouseEvent arg0) {
  if (Grid.mouseDragged) Grid.mouseDragged = false;
 }
 
 @Override
 public void mouseDragged(MouseEvent arg0) {
  Grid.mouseDragged = true;
  setActive(true);
 }

 @Override
 public void mouseMoved(MouseEvent arg0) {
  ;
 }
}
