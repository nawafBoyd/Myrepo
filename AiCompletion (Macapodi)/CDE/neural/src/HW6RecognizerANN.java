
import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;
import java.util.logging.Level;
import neural.neuralSolver;
import neural.solver;
import neural.weigths;

/**
 * Assignment No. 6
 * 
 * Due: October 1, 2012 (Monday) at 11:55PM
 * 
 * This class implements an artificial neural network handwritten character
 * images classifier. Refer to the accompanying .PDF file for the details of
 * this homework.
 */
public class HW6RecognizerANN implements RecognizerInterface {
        
	/*l
	 * This is the method that implements the artificial neural network.
	 * 
	 * (non-Javadoc)
	 * 
	 * @see RecognizerInterface#recognizerANN(double[])
	 */
	@Override
	public double[] recognizerANN(double[] inputArray) {
                
                
		double[] outputArray = new double[3];
                
                //System.out.print("DYN "+inputArray[0]);
                ;
               neuralSolver n=new neuralSolver();
                n.solve(inputArray.clone());
		return n.c;
	}
        
	/**
	 * This is the main method that starts the graphical user interface of the
	 * application. The recognizerANN() method of this class is called from
	 * inside the GUI application. Nothing needs to be done in this method.
	 * 
	 * @param args
	 *            The command-line arguments passed during the invocation of
	 *            this program (not used).
	 */
	public static void main(String[] args) {
		ANNOCRRecognizer.runApplication(new HW6RecognizerANN());
	}
}
