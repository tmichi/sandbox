#include <vtkUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCell.h>
#include <fstream>

int main( int argc, char** argv )
{

        vtkUnstructuredGridReader* reader = vtkUnstructuredGridReader::New();
        reader->SetFileName( argv[1] );
        reader->Update();

        std::ofstream fout( "out.obj" );
        if ( !fout ) return -1;

        vtkUnstructuredGrid* grid = reader->GetOutput();
        const int nblock = grid->GetNumberOfCells();

        for ( int i = 0; i < nblock; i++ ) {
                vtkCell* cell = grid->GetCell( i );

                vtkPoints* points = cell->GetPoints();
                const int npoints = points->GetNumberOfPoints();
                double cx = 0, cy = 0, cz = 0;
                for ( int j = 0; j < npoints; ++j ) {
                        double *p = points->GetPoint( j );
                        cx += p[0];
                        cy += p[1];
                        cz += p[2];
                }
                cx *= 1.0 / npoints;
                cy *= 1.0 / npoints;
                cz *= 1.0 / npoints;

                const int nfaces = cell->GetNumberOfFaces();
                for ( int j = 0; j < nfaces; ++j ) {
                        vtkCell* face = cell->GetFace( j ); // face is represented as vtkCell
                        const int nfpoints = face->GetNumberOfPoints();
                        for ( int k = 0; k < nfpoints; ++k ) {
                                double *p0 = face->GetPoints()->GetPoint( k );
                                p0[0] = 0.9 * p0[0] + 0.1 * cx;
                                p0[1] = 0.9 * p0[1] + 0.1 * cy;
                                p0[2] = 0.9 * p0[2] + 0.1 * cz;
                                fout << "v " << p0[0] << " " << p0[1] << " " << p0[2] << std::endl;
                        }
                }

        }

        int count = 1;
        for ( int i = 0; i < nblock; i++ ) {
                vtkCell* cell = grid->GetCell( i );
                const int nfaces = cell->GetNumberOfFaces();
                for ( int j = 0; j < nfaces; ++j ) {
                        fout << "f";
                        vtkCell* face = cell->GetFace( j );
                        const int nfpoints = face->GetNumberOfPoints();
                        for( int k = 0 ; k < nfpoints; ++k ) {
                                fout << " " << count;
                                count++;
                        }
                        fout << std::endl;
                }
        }
        return 0;
}
