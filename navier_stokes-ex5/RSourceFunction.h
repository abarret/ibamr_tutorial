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

#ifndef included_RSourceFunction
#define included_RSourceFunction

/////////////////////////////// INCLUDES /////////////////////////////////////

// IBAMR INCLUDES
#include <ibamr/AdvDiffHierarchyIntegrator.h>

#include <ibamr/app_namespaces.h>

/////////////////////////////// CLASS DEFINITION /////////////////////////////

/*!
 * \brief Class RSourceFunction provides forcing for the momentum equations
 * based on the Boussinesq approximation to the variable-density incompressible
 * Navier-Stokes equations.
 */
class RSourceFunction : public CartGridFunction
{
public:
    /*!
     * \brief Class constructor.
     */
    RSourceFunction(SAMRAI::tbox::Pointer<SAMRAI::pdat::CellVariable<NDIM, double> > Q_var,
                    SAMRAI::tbox::Pointer<SAMRAI::pdat::CellVariable<NDIM, double> > R_var,
                    SAMRAI::tbox::Pointer<IBAMR::AdvDiffHierarchyIntegrator> adv_diff_hier_integrator,
                    double kappa);

    /*!
     * \brief Empty destructor.
     */
    ~RSourceFunction();

    /*!
     * \name Methods to set patch data.
     */
    //\{

    /*!
     * \brief Indicates whether the concrete RSourceFunction object is
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
    Pointer<SAMRAI::pdat::CellVariable<NDIM, double> > d_Q_var, d_R_var;
    Pointer<AdvDiffHierarchyIntegrator> d_adv_diff_hier_integrator;
    double d_kappa = std::numeric_limits<double>::quiet_NaN();
};

//////////////////////////////////////////////////////////////////////////////

#endif // #ifndef included_RSourceFunction
