/******************************************************************************
 *
 * $Id$
 *
 * Project:  WindNinja
 * Purpose:  A concrete class for initializing WindNinja wind fields using
 *			 the point initialization input method (weather stations)
 * Author:   Jason Forthofer <jforthofer@gmail.com>
 *
 ******************************************************************************
 *
 * THIS SOFTWARE WAS DEVELOPED AT THE ROCKY MOUNTAIN RESEARCH STATION (RMRS)
 * MISSOULA FIRE SCIENCES LABORATORY BY EMPLOYEES OF THE FEDERAL GOVERNMENT 
 * IN THE COURSE OF THEIR OFFICIAL DUTIES. PURSUANT TO TITLE 17 SECTION 105 
 * OF THE UNITED STATES CODE, THIS SOFTWARE IS NOT SUBJECT TO COPYRIGHT 
 * PROTECTION AND IS IN THE PUBLIC DOMAIN. RMRS MISSOULA FIRE SCIENCES 
 * LABORATORY ASSUMES NO RESPONSIBILITY WHATSOEVER FOR ITS USE BY OTHER 
 * PARTIES,  AND MAKES NO GUARANTEES, EXPRESSED OR IMPLIED, ABOUT ITS QUALITY, 
 * RELIABILITY, OR ANY OTHER CHARACTERISTIC.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/

#ifndef POINT_INITIALIZATION_H
#define POINT_INITIALIZATION_H

#include "initialize.h"
#include "cellDiurnal.h"

#include <limits>	//for large number

#include "ogr_api.h"
#include "sstream"
#include "algorithm"
#include "iterator"
#include "string"
#include "iostream"
#include "fstream"
#include "math.h"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/posix_time/posix_time_io.hpp"
#include "boost/date_time/local_time_adjustor.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "gdal.h"
#include "cpl_conv.h"
#include "gdal_priv.h"
#include "gdal_util.h"




class pointInitialization : public initialize
{
	public:

		pointInitialization();								//Default constructor
		virtual ~pointInitialization();						// Destructor
		
		//pointInitialization(pointInitialization const& m);               // Copy constructor
		//pointInitialization& operator= (pointInitialization const& m);   // Assignment operator

		//Implementation of base class virtual function for initializing volume wind fields using the
		//domain averaged wind method.
		virtual void initializeFields(WindNinjaInputs &input,
		        Mesh const& mesh,
		        wn_3dScalarField& u0,
		        wn_3dScalarField& v0,
		        wn_3dScalarField& w0,
		        AsciiGrid<double>& cloud,
		        AsciiGrid<double>& L,
		        AsciiGrid<double>& u_star,
		        AsciiGrid<double>& bl_height);
        
        
        static void interpolateTimeData(WindNinjaInputs &input,std::vector<boost::posix_time::ptime> timeList);

        void stationCliCaller(bool station_fetch, std::string station_id, int nHours, bool btype,std::string fetcher,std::string radius, std::string limit, std::string pLat, std::string pLon, std::string LLLat, std::string LLLon, std::string URLat, std::string URLon , std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
//        void fetchSingleStation(std::string token,bool type,int nHours, std::string station_id, std::string svar,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
//        void fetchTest(std::string station_id, int nHours, string svar);
//        void fetchMultiStation(std::string token,bool type,int nHours, std::string station_ids, std::string svar,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
//        void fetchPointRadiusStation(std::string token,bool type,int nHours, std::string station_id,std::string radius, std::string limit, std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
//        void fetchLatLonStation(std::string token, bool type,int nHours, std::string lat, std::string lon, std::string radius, std::string limit, std::string svar,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
//        void fetchBboxStation(std::string token,bool type,int nHours,std::string lat1,std::string lon1,std::string lat2,std::string lon2,std::string svar,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
        
        void fetchSingleStation(bool type,int nHours, std::string station_id,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
        void fetchTest(std::string station_id, int nHours);
        void fetchMultiStation(bool type,int nHours, std::string station_ids,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
        void fetchPointRadiusStation(bool type,int nHours,std::string radius, std::string limit, std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
        void fetchLatLonStation(bool type,int nHours, std::string lat, std::string lon, std::string radius, std::string limit,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);
        void fetchBboxStation(bool type,int nHours,std::string lat1,std::string lon1,std::string lat2,std::string lon2,std::string yeara,std::string montha, std::string daya,std::string clocka,std::string yearb,std::string monthb,std::string dayb,std::string clockb);

        static bool fetchStationFromBbox(std::string stationFilename,
                                    std::string demFile, 
                                    std::vector<boost::posix_time::ptime> timeList);

        static std::vector<boost::posix_time::ptime> getTimeList( int startYear, int startMonth,
                                                int startDay, int startHour, int startMinute, int endYear,
                                                int endMonth, int endDay, int endHour, int endMinute,
                                                int nTimeSteps, std::string timeZone );

        void newAuto(AsciiGrid<double> &dem);
        int storeHour(int nHours);



    private:


                static const std::string dtoken;
                static const std::string dvar;
                static const std::string ndvar;
                static string BuildTime(std::string year_0,std::string month_0, std::string day_0,std::string clock_0,std::string year_1,std::string month_1,std::string day_1,std::string clock_1);
                static vector<string> UnifyTime(vector<boost::posix_time::ptime> timeList);
                static string IntConvert(int a);
                static vector<string> Split(char* str,const char* delim);
                void stringtoaster(int null,vector<int> vecnull);
                static vector<string>  InterpretCloudData(const double *dbCloud,int counter);
                static vector<vector<string> > VectorInterpretCloudData(vector<const double*>dbCloud,int smallcount, int largecount);
                static vector<string> CompareClouds(vector<string>low,vector<string>med,vector<string>high,int countlow,int countmed, int counthigh);
                static vector<string> UnifyClouds(const double *dvCloud,const double *dwCloud,const double *dxCloud,int count1,int count2,int count3,int backupcount);
                static void StringPrinter(char **stringdat, int counter, std::string name);
                static void FloatPrinter(const double *data, int counter,std::string name);
                static void VectorPrinter(std::vector<std::string> cata,std::string name);
                void doubleVectorPrinter(vector<const double*> cata,std::string name,int counter);
                void Irradiate(const double* solrad, int largecount);
                void UnifyRadiation(vector<double> radiation);
                static vector<string> fixWindDir(const double *winddir,std::string filler,int count);

                const char* BuildSingleUrl(std::string token, std::string station_id, std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                const char* BuildSingleLatest(std::string token, std::string station_id,std::string svar,int past, bool extendnetwork,std::string netids);
                const char* BuildMultiUrl(std::string token,std::string station_ids,std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                const char* BuildMultiLatest(std::string token, std::string station_ids,std::string svar,int past);
                const char* BuildRadiusLatest(std::string token, std::string station_id,std::string radius,std::string limit,std::string svar,int past);
                const char* BuildRadiusUrl(std::string token, std::string staion_id, std::string radius,std::string limit,std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                const char* BuildLatLonUrl(std::string token,std::string lat, std::string lon, std::string radius, std::string limit,std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                const char* BuildLatLonLatest(std::string token,std::string lat, std::string lon, std::string radius, std::string limit,std::string svar,int past);
                static std::string BuildBboxUrl(std::string lat1,std::string lon1, std::string lat2, std::string lon2,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                std::string BuildBboxLatest(std::string token,std::string lat1,std::string lon1, std::string lat2, std::string lon2,std::string svar,int past);
                static std::string BuildUnifiedBbox(double lat1,double lon1, double lat2,double lon2,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);

                //                const char* BuildBboxUrl(std::string token,std::string lat1,std::string lon1, std::string lat2, std::string lon2,std::string svar,std::string yearx,std::string monthx, std::string dayx,std::string clockx,std::string yeary,std::string monthy,std::string dayy,std::string clocky);
                //                const char* BuildBboxLatest(std::string token,std::string lat1,std::string lon1, std::string lat2, std::string lon2,std::string svar,int past);




                double dfInvDistWeight;

};

#endif /* POINT_INITIALIZATION_H */
