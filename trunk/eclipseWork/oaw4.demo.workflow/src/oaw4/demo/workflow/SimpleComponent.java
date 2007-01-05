/**
 * 
 */
package oaw4.demo.workflow;


import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.openarchitectureware.workflow.WorkflowComponent;
import org.openarchitectureware.workflow.WorkflowContext;
import org.openarchitectureware.workflow.ast.parser.Location;
import org.openarchitectureware.workflow.container.CompositeComponent;
import org.openarchitectureware.workflow.issues.Issues;
import org.openarchitectureware.workflow.monitor.ProgressMonitor;

/**
 * @author behrenan
 *
 */
public class SimpleComponent implements WorkflowComponent {
	private static final Log LOG = LogFactory.getLog(SimpleComponent.class);
	private String message = "hu";
	
	
	public void checkConfiguration(Issues arg0) {
	}

	public void invoke(WorkflowContext ctx, ProgressMonitor monitor, Issues issues) {
		LOG.info("hier");
		ctx.set(WorkflowContext.DEFAULT_SLOT, message);
	}

	/* (non-Javadoc)
	 * @see org.openarchitectureware.workflow.WorkflowComponent#getContainer()
	 */
	public CompositeComponent getContainer() {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.openarchitectureware.workflow.WorkflowComponent#getLocation()
	 */
	public Location getLocation() {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.openarchitectureware.workflow.WorkflowComponent#setContainer(org.openarchitectureware.workflow.container.CompositeComponent)
	 */
	public void setContainer(CompositeComponent arg0) {
		// TODO Auto-generated method stub
		
	}

	/* (non-Javadoc)
	 * @see org.openarchitectureware.workflow.WorkflowComponent#setLocation(org.openarchitectureware.workflow.ast.parser.Location)
	 */
	public void setLocation(Location arg0) {
		// TODO Auto-generated method stub
		
	}

	/**
	 * @return the message
	 */
	public String getMessage() {
		return message;
	}

	/**
	 * @param message the message to set
	 */
	public void setMessage(String message) {
		this.message = message;
	}
}