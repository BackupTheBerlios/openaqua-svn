// license-header java merge-point
package org.andromda.timetracker.web;

import org.apache.struts.action.ActionMapping;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @see org.andromda.timetracker.web.SearchController
 */
public class SearchControllerImpl extends SearchController
{
    /**
     * @see org.andromda.timetracker.web.SearchController#populateSearchScreen(org.apache.struts.action.ActionMapping, org.andromda.timetracker.web.PopulateSearchScreenForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
     */
    public final void populateSearchScreen(ActionMapping mapping, org.andromda.timetracker.web.PopulateSearchScreenForm form, HttpServletRequest request, HttpServletResponse response) throws Exception
    {
        // setting a date
        form.setStartDateMinimumAsDate(new java.util.Date());
        // this property receives a default value, just to have the application running on dummy data
        form.setSubmitter(new Long((long)348678409));
        form.setSubmitterValueList(new Object[] {"submitter-1", "submitter-2", "submitter-3", "submitter-4", "submitter-5"});
        form.setSubmitterLabelList(form.getSubmitterValueList());
        // setting a date
        form.setStartDateMaximumAsDate(new java.util.Date());
        // this property receives a default value, just to have the application running on dummy data
        form.setStatus("status-test");
        form.setStatusValueList(new Object[] {"status-1", "status-2", "status-3", "status-4", "status-5"});
        form.setStatusLabelList(form.getStatusValueList());
        // this property receives a default value, just to have the application running on dummy data
        form.setApprover(new Long((long)1185244869));
        form.setApproverValueList(new Object[] {"approver-1", "approver-2", "approver-3", "approver-4", "approver-5"});
        form.setApproverLabelList(form.getApproverValueList());
    }

}