package corbaclient;

import connector.GetUidHelper;
import connector.GetUidImpl;
import java.io.PrintWriter;
import java.io.FileWriter;
import java.io.BufferedWriter;

public class Main {
  public static void main(String[] args) {
    try {
      // Initialize the ORB.
      org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args,null);

      // Create a uid  object.
      GetUidImpl uid =     new GetUidHelper.bind();
            
      // Let the ORB know about the object
      orb.connect(uid);

      // Write stringified object reference to a file
      PrintWriter out = new PrintWriter(new BufferedWriter(  new FileWriter(args[0])));
      out.println(  orb.object_to_string(uid) );
      out.close();

      // wait for invocations from clients
      java.lang.Object sync =  new java.lang.Object();
      synchronized (sync) {
        sync.wait();
      }
    } catch (Exception e) {
      System.err.println( "Stock server error: " + e);
      e.printStackTrace(System.out);
    }
  }
}