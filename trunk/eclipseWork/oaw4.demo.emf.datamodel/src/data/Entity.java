/**
 * <copyright>
 * </copyright>
 *
 * $Id$
 */
package data;

import org.eclipse.emf.common.util.EList;

/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Entity</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link data.Entity#getAttribute <em>Attribute</em>}</li>
 * </ul>
 * </p>
 *
 * @see data.DataPackage#getEntity()
 * @model
 * @generated
 */
public interface Entity extends Element {
	/**
	 * Returns the value of the '<em><b>Attribute</b></em>' containment reference list.
	 * The list contents are of type {@link data.Attribute}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Attribute</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Attribute</em>' containment reference list.
	 * @see data.DataPackage#getEntity_Attribute()
	 * @model type="data.Attribute" containment="true" required="true"
	 * @generated
	 */
	EList getAttribute();

} // Entity