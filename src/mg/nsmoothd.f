c* ///////////////////////////////////////////////////////////////////////////
c* @file    nsmoothd.f
c* @author  Michael Holst
c* @brief   Generic nonlinear smoothing iteration.
c* @version $Id$
c* @attention
c* @verbatim
c*
c* PMG -- Parallel algebraic MultiGrid
c* Copyright (c) 1994-2006.  Michael Holst.
c*
c* Michael Holst <mholst@math.ucsd.edu>
c* University of California, San Diego
c* Department of Mathematics, 5739 AP&M
c* 9500 Gilman Drive, Dept. 0112
c* La Jolla, CA 92093-0112 USA                                                  
c* http://math.ucsd.edu/~mholst
c*
c* This file is part of PMG.
c*
c* PMG is free software; you can redistribute it and/or modify
c* it under the terms of the GNU General Public License as published by
c* the Free Software Foundation; either version 2 of the License, or
c* (at your option) any later version.
c*
c* PMG is distributed in the hope that it will be useful,
c* but WITHOUT ANY WARRANTY; without even the implied warranty of
c* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
c* GNU General Public License for more details.
c*
c* You should have received a copy of the GNU General Public License
c* along with PMG; if not, write to the Free Software
c* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
c*
c* Linking PMG statically or dynamically with other modules is making a
c* combined work based on PMG. Thus, the terms and conditions of the GNU
c* General Public License cover the whole combination.
c* 
c* SPECIAL GPL EXCEPTION
c* In addition, as a special exception, the copyright holders of PMG
c* give you permission to combine the PMG program with free software
c* programs and libraries that are released under the GNU LGPL or with
c* code included in releases of ISIM, Ion Simulator Interface, PMV, PyMOL
c* SMOL, VMD, and Vision. Such combined software may be linked with PMG and 
c* redistributed together in original or modified form as mere aggregation
c* without requirement that the entire work be under the scope of the GNU 
c* General Public License. This special exception permission is also extended
c* to any software listed in the SPECIAL GPL EXCEPTION clauses by the FEtk and
c* APBS libraries.
c* 
c* Note that people who make modified versions of PMG are not obligated
c* to grant this special exception for their modified versions; it is
c* their choice whether to do so. The GNU General Public License gives
c* permission to release a modified version without this exception; this
c* exception also makes it possible to release a modified version which
c* carries forward this exception.
c*
c* @endverbatim
c* ///////////////////////////////////////////////////////////////////////////

      subroutine nsmooth(nx,ny,nz,ipc,rpc,ac,cc,fc,x,w1,w2,r,
     2   itmax,iters,errtol,omega,iresid,iadjoint,meth)
c* *********************************************************************
c* purpose: 
c*
c*    call the appropriate nonlinear smoothing routine.
c*
c* author:  michael holst
c* *********************************************************************
      implicit         none
      integer          ipc(*),itmax,iters,iresid,iadjoint,nx,ny,nz,meth
      double precision omega,errtol
      double precision rpc(*),ac(nx*ny*nz,*),cc(nx,ny,nz),fc(nx,ny,nz)
      double precision x(nx,ny,nz),w1(nx,ny,nz),w2(nx,ny,nz)
      double precision r(nx,ny,nz)
c*
cmdir 0 0
c*
c*    *** do in one step ***
      if (meth .eq. 0) then
         call nwjac(nx,ny,nz,ipc,rpc,ac,cc,fc,x,w1,w2,r,
     2      itmax,iters,errtol,omega,iresid,iadjoint)
      elseif (meth .eq. 1) then
         call ngsrb(nx,ny,nz,ipc,rpc,ac,cc,fc,x,w1,w2,r,
     2      itmax,iters,errtol,omega,iresid,iadjoint)
      elseif (meth .eq. 2) then
         call nsor(nx,ny,nz,ipc,rpc,ac,cc,fc,x,w1,w2,r,
     2      itmax,iters,errtol,omega,iresid,iadjoint)
      elseif (meth .eq. 3) then
         call nrich(nx,ny,nz,ipc,rpc,ac,cc,fc,x,w1,w2,r,
     2      itmax,iters,errtol,omega,iresid,iadjoint)
      else
         call vnmprt(2,'% NSMOOTH: bad smoothing routine specified...',
     2      45)
      endif
c*
c*    *** return and end ***
      return
      end

