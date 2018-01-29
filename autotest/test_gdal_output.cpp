/******************************************************************************
 *
 * Project:  WindNinja
 * Purpose:  Test gdal output
 * Author:   Kyle Shannon <kyle at pobox dot com>
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

#ifndef WIN32
#include <boost/test/unit_test.hpp>

#include "gdal_output.h"

BOOST_AUTO_TEST_SUITE(gdal_output)

BOOST_AUTO_TEST_CASE(shapefile) {
  GDALAllRegister();
  int rc = 0;
  AsciiGrid<double> spd(10, 10, 0, 0, 10, -9999);
  AsciiGrid<double> dir(spd);
  rc = NinjaGDALOutput("ESRI Shapefile", "test.shp", 0, spd, dir, 0);
  BOOST_REQUIRE(rc == 0);
}

BOOST_AUTO_TEST_CASE(write_arrow) {
  GDALAllRegister();
  int rc = 0;
  AsciiGrid<double> spd(10, 10, 0, 0, 10, -9999);
  AsciiGrid<double> dir(spd);
  rc = NinjaGDALOutput("ESRI Shapefile", "arrow.shp", NINJA_OUTPUT_ARROWS, spd, dir, 0);
  BOOST_REQUIRE(rc == 0);
}

BOOST_AUTO_TEST_CASE(kml) {
  GDALAllRegister();
  int rc = 0;
  AsciiGrid<double> spd(10, 10, 0, 0, 10, -9999);
  AsciiGrid<double> dir(spd);
  rc = NinjaGDALOutput("LIBKML", "test.kml", NINJA_OUTPUT_ARROWS, spd, dir, 0);
  BOOST_REQUIRE(rc == 0);
}

BOOST_AUTO_TEST_CASE(kmz) {
  GDALAllRegister();
  int rc = 0;
  AsciiGrid<double> spd(10, 10, 0, 0, 10, -9999);
  AsciiGrid<double> dir(spd);
  rc = NinjaGDALOutput("LIBKML", "test.kmz", NINJA_OUTPUT_ARROWS, spd, dir, 0);
  BOOST_REQUIRE(rc == 0);
}

BOOST_AUTO_TEST_SUITE_END()

#endif /* WIN32 */