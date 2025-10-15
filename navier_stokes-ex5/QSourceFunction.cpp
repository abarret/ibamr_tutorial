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
#include "QSourceFunction.h"

/////////////////////////////// PUBLIC ///////////////////////////////////////

QSourceFunction::QSourceFunction(Pointer<Variable<NDIM> > Q_var,
                                 Pointer<AdvDiffHierarchyIntegrator> adv_diff_hier_integrator)
    : d_Q_var(Q_var), d_adv_diff_hier_integrator(adv_diff_hier_integrator)
{
    // intentionally blank
    return;
} // QSourceFunction

QSourceFunction::~QSourceFunction()
{
    // intentionally blank
    return;
} // ~QSourceFunction

bool
QSourceFunction::isTimeDependent() const
{
    return true;
} // isTimeDependent

void
QSourceFunction::setDataOnPatch(const int data_idx,
                                Pointer<Variable<NDIM> > /*var*/,
                                Pointer<Patch<NDIM> > patch,
                                const double /*data_time*/,
                                const bool initial_time,
                                Pointer<PatchLevel<NDIM> > /*patch_level*/)
{
    return;
} // setDataOnPatch

//////////////////////////////////////////////////////////////////////////////
