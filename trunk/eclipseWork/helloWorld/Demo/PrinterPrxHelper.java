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

public final class PrinterPrxHelper extends Ice.ObjectPrxHelperBase implements PrinterPrx
{
    public void
    printString(String s)
    {
	printString(s, __defaultContext());
    }

    public void
    printString(String s, java.util.Map __ctx)
    {
	int __cnt = 0;
	while(true)
	{
	    try
	    {
		Ice._ObjectDel __delBase = __getDelegate();
		_PrinterDel __del = (_PrinterDel)__delBase;
		__del.printString(s, __ctx);
		return;
	    }
	    catch(IceInternal.LocalExceptionWrapper __ex)
	    {
		__handleExceptionWrapper(__ex);
	    }
	    catch(Ice.LocalException __ex)
	    {
		__cnt = __handleException(__ex, __cnt);
	    }
	}
    }

    public static PrinterPrx
    checkedCast(Ice.ObjectPrx __obj)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (PrinterPrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::Demo::Printer"))
		{
		    PrinterPrxHelper __h = new PrinterPrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static PrinterPrx
    checkedCast(Ice.ObjectPrx __obj, java.util.Map __ctx)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    try
	    {
		__d = (PrinterPrx)__obj;
	    }
	    catch(ClassCastException ex)
	    {
		if(__obj.ice_isA("::Demo::Printer", __ctx))
		{
		    PrinterPrxHelper __h = new PrinterPrxHelper();
		    __h.__copyFrom(__obj);
		    __d = __h;
		}
	    }
	}
	return __d;
    }

    public static PrinterPrx
    checkedCast(Ice.ObjectPrx __obj, String __facet)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::Demo::Printer"))
		{
		    PrinterPrxHelper __h = new PrinterPrxHelper();
		    __h.__copyFrom(__bb);
		    __d = __h;
		}
	    }
	    catch(Ice.FacetNotExistException ex)
	    {
	    }
	}
	return __d;
    }

    public static PrinterPrx
    checkedCast(Ice.ObjectPrx __obj, String __facet, java.util.Map __ctx)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    try
	    {
		if(__bb.ice_isA("::Demo::Printer", __ctx))
		{
		    PrinterPrxHelper __h = new PrinterPrxHelper();
		    __h.__copyFrom(__bb);
		    __d = __h;
		}
	    }
	    catch(Ice.FacetNotExistException ex)
	    {
	    }
	}
	return __d;
    }

    public static PrinterPrx
    uncheckedCast(Ice.ObjectPrx __obj)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    PrinterPrxHelper __h = new PrinterPrxHelper();
	    __h.__copyFrom(__obj);
	    __d = __h;
	}
	return __d;
    }

    public static PrinterPrx
    uncheckedCast(Ice.ObjectPrx __obj, String __facet)
    {
	PrinterPrx __d = null;
	if(__obj != null)
	{
	    Ice.ObjectPrx __bb = __obj.ice_facet(__facet);
	    PrinterPrxHelper __h = new PrinterPrxHelper();
	    __h.__copyFrom(__bb);
	    __d = __h;
	}
	return __d;
    }

    protected Ice._ObjectDelM
    __createDelegateM()
    {
	return new _PrinterDelM();
    }

    protected Ice._ObjectDelD
    __createDelegateD()
    {
	return new _PrinterDelD();
    }

    public static void
    __write(IceInternal.BasicStream __os, PrinterPrx v)
    {
	__os.writeProxy(v);
    }

    public static PrinterPrx
    __read(IceInternal.BasicStream __is)
    {
	Ice.ObjectPrx proxy = __is.readProxy();
	if(proxy != null)
	{
	    PrinterPrxHelper result = new PrinterPrxHelper();
	    result.__copyFrom(proxy);
	    return result;
	}
	return null;
    }
}
