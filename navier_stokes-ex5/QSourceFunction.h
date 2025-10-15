// ---------------------------------------------------------------------
//
// Copyright (c) 2014 - 2024 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

#ifndef included_QSourceFunction
#define included_QSourceFunction

/////////////////////////////// INCLUDES /////////////////////////////////////

// IBAMR INCLUDES
#include <ibamr/AdvDiffHierarchyIntegrator.h>

#include <ibamr/app_namespaces.h>

/////////////////////////////// CLASS DEFINITION /////////////////////////////

/*!
 * \brief Class QSourceFunction provides forcing for the momentum equations
 * based on the Boussinesq approximation to the variable-density incompressible
 * Navier-Stokes equations.
 */
class QSourceFunction : public CartGridFunction
{
public:
    /*!
     * \brief Class constructor.
     */
    QSourceFunction(Pointer<Variable<NDIM> > Q_var, Pointer<AdvDiffHierarchyIntegrator> adv_diff_hier_integrator);

    /*!
     * \brief Empty destructor.
     */
    ~QSourceFunction();

    /*!
     * \name Methods to set patch data.
     */
    //\{

    /*!
     * \brief Indicates whether the concrete QSourceFunction object is
     * time-dependent.
     */
    bool isTimeDependent() const;

    /*!
     * \brief Evaluate the function on the patch interior.
     */
    void setDataOnPatch(const int data_idx,
                        Pointer<Variable<NDIM> > var,
                        Pointer<Patch<NDIM> > patch,
                        const double data_time,
                        const bool initial_time = false,
                        Pointer<PatchLevel<NDIM> > patch_level = nullptr) override;

    //\}

private:
    Pointer<Variable<NDIM> > d_Q_var;
    Pointer<AdvDiffHierarchyIntegrator> d_adv_diff_hier_integrator;
};

//////////////////////////////////////////////////////////////////////////////

#endif // #ifndef included_QSourceFunction
