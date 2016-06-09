/**
 * .pcd ファイル書き出しの方法、というかPointCloudデータの作成方法。
 *
 */
#include <iostream>
#include <pcl/io/pcd_io.h>

int main ( int argc, char** argv )
{
        pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr ( new pcl::PointCloud<pcl::PointXYZ>() );
        pcl::PointCloud<pcl::PointXYZ>& point_cloud = *point_cloud_ptr;

        for ( float x=-0.5f; x<=0.5f; x+=0.01f ) {
                for ( float y=-0.5f; y<=0.5f; y+=0.01f ) {
                        pcl::PointXYZ point;
                        point.x = x;
                        point.y = y;
                        point.z = 2.0f - y;
                        point_cloud.points.push_back ( point );
                }
        }
        point_cloud.width = static_cast<int>( point_cloud.points.size() );
        point_cloud.height = 1;

        if ( pcl::io::savePCDFile( "hoge.pcd", point_cloud ) == - 1 ) {
                std::cerr<<"save failed."<<std::endl;
        }
        return 0;
}
