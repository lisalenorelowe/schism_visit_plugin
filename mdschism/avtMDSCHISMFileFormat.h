/*****************************************************************************
*
* Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtMDSCHISMFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_MDSCHISM_FILE_FORMAT_H
#define AVT_MDSCHISM_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>
#include "FileFormatFavorInterface.h"
#include <vector>
#include <avtMDSCHISMFileFormatImpl.h>


// ****************************************************************************
//  Class: avtMDSCHISMFileFormat
//
//  Purpose:
//      Reads in MDSCHISM files as a plugin to VisIt.
//
//  Programmer: qshu -- generated by xml2avt
//  Creation:   Fri Jul 31 10:54:14 PDT 2020
//
// ****************************************************************************

class avtMDSCHISMFileFormat : public avtMTMDFileFormat
{
  public:
                       avtMDSCHISMFileFormat(const char *);
    virtual           ~avtMDSCHISMFileFormat() {;};

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, int timestep, 
    //                                     int domain, const char *type, void *args, 
    //                                     DestructorFunction &);
    //

    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    // virtual void        GetCycles(std::vector<int> &);
     virtual void        GetTimes(std::vector<double> &);
	 virtual void                ActivateTimestep(void);
    //

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "MDSCHISM"; };
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);



	avtVariableCache * get_cache();

  protected:
    // DATA MEMBERS

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
	void           PopulateStateMetaData(avtDatabaseMetaData * a_metaData,
		int                   a_timeState);

	void           addFaceCenterData(avtDatabaseMetaData * a_metaData,
		SCHISMVar10            * a_varPtr,
		const std::string   & a_varName,
		const std::string   & a_varLabel,
		const avtCentering  & a_center);

	void           addNodeCenterData(avtDatabaseMetaData * a_metaData,
		SCHISMVar10            * a_varPtr,
		const std::string   & a_varName,
		const std::string   & a_varLabel,
		const avtCentering  & a_center);

	void           addSideCenterData(avtDatabaseMetaData * a_metaData,
		SCHISMVar10            * a_varPtr,
		const std::string   & a_varName,
		const std::string   & a_varLabel,
		const avtCentering  & a_center);
	
  private:

	//std::unique_ptr<FileFormatFavorInterface> m_impl;
	  avtMDSCHISMFileFormatImpl * m_impl;
	  //both just first data file and mesh provider from impl
	  MDSchismOutput * m_data;
	  MDSCHISMMeshProvider * m_mesh;

	  std::string  m_mesh_3d;
	  std::string  m_layer_mesh;
	  std::string  m_mesh_2d;
	  std::string  m_mesh_2d_no_wet_dry;
	  std::string  m_side_center_point_3d_mesh;
	  std::string  m_side_center_point_2d_mesh;
	  // vertical side-faces center points, 3d flux data uses it
	  std::string  m_face_center_point_3d_mesh;
	  std::string  m_node_surface;
	  std::string  m_node_depth;
	  std::string  m_surface_state_suffix;
	  std::string  m_bottom_state_suffix;
	  std::string  m_depth_average_suffix;
	  std::string  m_node_depth_label;
	  std::string  m_node_surface_label;

	  //map convert var label into netcdf varname token
	  std::map<std::string, std::string>  m_var_name_label_map;


	  //map convert var label into netcdf varname token
	  std::map<std::string, std::string>  m_var_vertical_center_map;


	  //map convert var label into netcdf varname token
	  std::map<std::string, std::string>  m_var_horizontal_center_map;


	  // maping var label to its mesh name
	  std::map<std::string, std::string> m_var_mesh_map;

	  // caching SCHISM var (not visit labeled var)  dim 3D/2D only
	  std::map<std::string, int> m_var_dim;
public:
	std::string m_data_file;
};


#endif
