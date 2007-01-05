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
 * A representation of the model object '<em><b>Model</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link data.Model#getEntity <em>Entity</em>}</li>
 * </ul>
 * </p>
 *
 * @see data.DataPackage#getModel()
 * @model
 * @generated
 */
public interface Model extends Element {
	/**
	 * Returns the value of the '<em><b>Entity</b></em>' containment reference list.
	 * The list contents are of type {@link data.Entity}.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Entity</em>' containment reference list isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Entity</em>' containment reference list.
	 * @see data.DataPackage#getModel_Entity()
	 * @model type="data.Entity" containment="true" required="true"
	 * @generated
	 */
	EList getEntity();

} // Model