// ---------------------------------------------------------------------
//
// Copyright (c) 2014 - 2020 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

#include <HierarchyDataOpsManager.h>
#include <SAMRAI_config.h>

// Local includes
#include "RSourceFunction.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

RSourceFunction::RSourceFunction(Pointer<CellVariable<NDIM, double> > Q_var,
                                 Pointer<CellVariable<NDIM, double> > R_var,
                                 Pointer<AdvDiffHierarchyIntegrator> adv_diff_hier_integrator,
                                 const double kappa)
    : d_Q_var(Q_var), d_R_var(R_var), d_adv_diff_hier_integrator(adv_diff_hier_integrator), d_kappa(kappa)
{
    // intentionally blank
    return;
} // RSourceFunction

RSourceFunction::~RSourceFunction()
{
    // intentionally blank
    return;
} // ~RSourceFunction

bool
RSourceFunction::isTimeDependent() const
{
    return true;
} // isTimeDependent

void
RSourceFunction::setDataOnPatch(const int data_idx,
                                Pointer<Variable<NDIM> > /*var*/,
                                Pointer<Patch<NDIM> > patch,
                                const double /*data_time*/,
                                const bool initial_time,
                                Pointer<PatchLevel<NDIM> > /*patch_level*/)
{
    if (initial_time) return;
    Pointer<CellData<NDIM, double> > return_data = patch->getPatchData(data_idx);
    Pointer<CellData<NDIM, double> > Q_data =
        patch->getPatchData(d_Q_var, d_adv_diff_hier_integrator->getCurrentContext());
    Pointer<CellData<NDIM, double> > R_data =
        patch->getPatchData(d_R_var, d_adv_diff_hier_integrator->getCurrentContext());

    for (CellIterator<NDIM> ci(patch->getBox()); ci; ci++)
    {
        const CellIndex<NDIM>& idx = ci();
        (*return_data)(idx) = d_kappa * (*Q_data)(idx) * (1.0 - (*R_data)(idx));
    }
    return;
} // setDataOnPatch

//////////////////////////////////////////////////////////////////////////////
