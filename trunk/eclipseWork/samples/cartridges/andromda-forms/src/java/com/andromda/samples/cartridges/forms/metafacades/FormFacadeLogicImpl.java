package com.andromda.samples.cartridges.forms.metafacades;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import org.andromda.metafacades.uml.AttributeFacade;
import org.andromda.metafacades.uml.ClassifierFacade;
import org.andromda.metafacades.uml.DependencyFacade;
import org.andromda.metafacades.uml.ModelElementFacade;

import com.andromda.samples.cartridges.forms.psm.FormField;
import com.andromda.samples.cartridges.forms.psm.FormSection;

/**
 * MetafacadeLogic implementation for
 * com.andromda.samples.cartridges.forms.metafacades.FormFacade.
 * 
 * @see com.andromda.samples.cartridges.forms.metafacades.FormFacade
 */
public class FormFacadeLogicImpl extends FormFacadeLogic
{

    public FormFacadeLogicImpl(Object metaObject, String context)
    {
        super(metaObject, context);
    }

    /**
     * @see com.andromda.samples.cartridges.forms.metafacades.FormFacade#getFormTitle()
     */
    protected java.lang.String handleGetFormTitle()
    {
        return "Form for class " + this.getFullyQualifiedName();
    }

    /**
     * @see com.andromda.samples.cartridges.forms.metafacades.FormFacade#getFormSections()
     */
    protected java.util.Collection handleGetFormSections()
    {
        ArrayList sections = new ArrayList();
        Collection sourceDependencies = this.getSourceDependencies();
        for (Iterator iter = sourceDependencies.iterator(); iter.hasNext();)
        {
            DependencyFacade element = (DependencyFacade) iter.next();
            ModelElementFacade targetElement = element.getTargetElement();
            if (targetElement instanceof ClassifierFacade)
            {
                ClassifierFacade otherClass = (ClassifierFacade) targetElement;
                FormSection section = transformClassifierToFormSection(otherClass);
                sections.add(section);
            }
        }
        return sections;
    }

    /**
     * Transforms all attribute inside a classifier into FormFields inside a
     * FormSection.
     * 
     * @param theClass
     *            the Classifier to transform
     * @return the transformed FormSection
     */
    private FormSection transformClassifierToFormSection(ClassifierFacade theClass)
    {
        FormSection section = new FormSection("Fields for " + theClass.getFullyQualifiedName(),
                new ArrayList());
        for (Iterator iter = theClass.getAttributes().iterator(); iter.hasNext();)
        {
            AttributeFacade element = (AttributeFacade) iter.next();
            section.getFormfields().add(new FormField(element.getName(), 40));
        }
        return section;
    }
}