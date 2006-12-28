// **********************************************************************
//
// Copyright (c) 2003-2006 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.1.1

package Demo;

public final class _PrinterDelD extends Ice._ObjectDelD implements _PrinterDel
{
    public void
    printString(String s, java.util.Map __ctx)
	throws IceInternal.LocalExceptionWrapper
    {
	Ice.Current __current = new Ice.Current();
	__initCurrent(__current, "printString", Ice.OperationMode.Normal, __ctx);
	while(true)
	{
	    IceInternal.Direct __direct = new IceInternal.Direct(__current);
	    try
	    {
		Printer __servant = null;
		try
		{
		    __servant = (Printer)__direct.servant();
		}
		catch(ClassCastException __ex)
		{
		    Ice.OperationNotExistException __opEx = new Ice.OperationNotExistException();
		    __opEx.id = __current.id;
		    __opEx.facet = __current.facet;
		    __opEx.operation = __current.operation;
		    throw __opEx;
		}
		try
		{
		    __servant.printString(s, __current);
		    return;
		}
		catch(Ice.LocalException __ex)
		{
		    throw new IceInternal.LocalExceptionWrapper(__ex, false);
		}
	    }
	    finally
	    {
		__direct.destroy();
	    }
	}
    }
}
