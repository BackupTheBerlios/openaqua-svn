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

public final class PrinterHolder
{
    public
    PrinterHolder()
    {
    }

    public
    PrinterHolder(Printer value)
    {
	this.value = value;
    }

    public class Patcher implements IceInternal.Patcher
    {
	public void
	patch(Ice.Object v)
	{
	    value = (Printer)v;
	}

	public String
	type()
	{
	    return "::Demo::Printer";
	}
    }

    public Patcher
    getPatcher()
    {
	return new Patcher();
    }

    public Printer value;
}
