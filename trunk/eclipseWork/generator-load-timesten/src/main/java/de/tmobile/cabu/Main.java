/**
 * 
 */
package de.tmobile.cabu;



/**
 * @author behrenan
 *
 */
public class Main {

	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
        System.out.println( "Start Load Test" );
        long start = System.currentTimeMillis();
        
        //TODO Setup database??
        //setup threads
        TTGenerator[] threadArray = new TTGenerator[Configuration.getInstance().getMaxConnections()];
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	threadArray[i] = new TTGenerator( "" + i );
        }
        

        //fire up all threads
        Stats.getInstance().setGlobalTime(System.nanoTime());
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	threadArray[i].start();
        }
        
        //wait for finish
        for (int i = 0; i < Configuration.getInstance().getMaxConnections(); i++) {
        	threadArray[i].join();
    		//System.out.println( "Finished Generator Run with Connection ID " + getName());
        }
        long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();
        long runTime = System.currentTimeMillis() - start;
        
        //nothing more to do. Systems waits upuntil all threads are finished

        //wait for finishing
        //Stats.getInstance().setGlobalTime(System.nanoTime());
        //while(ttGroup.activeCount()==0);
		//long diff = System.nanoTime()-Stats.getInstance().getGlobalTime();
        
        double ms = diff/1000000; //yepp, durch 10000. Oder???
        double msP = ms/Configuration.getInstance().getMaxConnections();
        System.out.println( "Finished Load Test in " + ms +" ms = " + msP + " ms/Connection ");
        System.out.println( "Runtime was " +runTime + "ms");
        
	}

}
