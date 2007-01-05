/**
 * 
 */
package oaw4.demo.workflow;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.openarchitectureware.workflow.WorkflowContext;
import org.openarchitectureware.workflow.issues.Issues;
import org.openarchitectureware.workflow.lib.WorkflowComponentWithModelSlot;
import org.openarchitectureware.workflow.monitor.ProgressMonitor;

/**
 * @author behrenan
 *
 */
public class MessageOutputComponent extends WorkflowComponentWithModelSlot {
	private static final Log LOG = LogFactory.getLog(SimpleComponent.class);

	/* (non-Javadoc)
	 * @see org.openarchitectureware.workflow.WorkflowComponent#invoke(org.openarchitectureware.workflow.WorkflowContext, org.openarchitectureware.workflow.monitor.ProgressMonitor, org.openarchitectureware.workflow.issues.Issues)
	 */
	public void invoke(WorkflowContext ctx, ProgressMonitor monitor, Issues issues) {
		LOG.info("da");
		String message = (String) ctx.get(WorkflowContext.DEFAULT_SLOT);
		if (message!=null) LOG.info(message);

	}

}

