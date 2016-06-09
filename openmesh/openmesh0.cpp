#include <iostream>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Tools/Decimater/DecimaterT.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Decimater/ModQuadricT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<>                      Mesh;
typedef OpenMesh::Decimater::DecimaterT< Mesh >               Decimater;
typedef OpenMesh::Decimater::ModQuadricT< Mesh >::Handle HModQuadric;
/*
int main(int argc, char **argv)
{
	
	Mesh        mesh;             // a mesh object
	// check command line options
	if (argc != 4) 
	{
		std::cerr << "Usage:  " << argv[0] << " #iterations infile outfile\n";
		return 1;
	}
	// read mesh from stdin
	if ( ! OpenMesh::IO::read_mesh(mesh, argv[2]) ) {
		
		std::cerr << "Error: Cannot read mesh from " << argv[2] << std::endl;
		return 1;
	}

	Decimater   decimater(mesh);  // a decimater object, connected to a mesh
	HModQuadric hModQuadric;      // use a quadric module
	decimater.add( hModQuadric ); // register module at the decimater
	std::cout << decimater.module( hModQuadric ).name() << std::endl;
	decimater.initialize();       // let the decimater initialize the mesh and the
	decimater.decimate_to(50);


	mesh.garbage_collection();


	// write mesh to stdout
	if ( ! OpenMesh::IO::write_mesh(mesh, argv[3]) )
	{
		std::cerr << "Error: cannot write mesh to " << argv[3] << std::endl;
		return 1;
	}
	return 0;
}

*/
int main()
{
	Mesh mesh;	
	Mesh::VertexHandle vhandle[7];
        vhandle[0] = mesh.add_vertex( Mesh::Point( -1, 1, 0 ) );
        vhandle[1] = mesh.add_vertex( Mesh::Point( -1, 3, 0 ) );
        vhandle[2] = mesh.add_vertex( Mesh::Point( 0, 0, 0 ) );
        vhandle[3] = mesh.add_vertex( Mesh::Point( 0, 2, 0 ) );
        vhandle[4] = mesh.add_vertex( Mesh::Point( 0, 4, 0 ) );
        vhandle[5] = mesh.add_vertex( Mesh::Point( 1, 1, 0 ) );
        vhandle[6] = mesh.add_vertex( Mesh::Point( 1, 3, 0 ) );
// Add three quad faces
        std::vector<Mesh::VertexHandle> face_vhandles;
        face_vhandles.push_back( vhandle[1] );
        face_vhandles.push_back( vhandle[0] );
        face_vhandles.push_back( vhandle[2] );
        face_vhandles.push_back( vhandle[3] );
        mesh.add_face( face_vhandles );
        face_vhandles.clear();
        face_vhandles.push_back( vhandle[1] );
        face_vhandles.push_back( vhandle[3] );
        face_vhandles.push_back( vhandle[5] );
        face_vhandles.push_back( vhandle[4] );
        mesh.add_face( face_vhandles );
        face_vhandles.clear();
        face_vhandles.push_back( vhandle[3] );
        face_vhandles.push_back( vhandle[2] );
        face_vhandles.push_back( vhandle[6] );
        face_vhandles.push_back( vhandle[5] );
        mesh.add_face( face_vhandles );
	if ( ! OpenMesh::IO::write_mesh(mesh, "sample.obj") )
	{
		return 1;
	}
/*// Now find the edge between vertex vhandle[2]
// and vhandle[3]
        for( 	Mesh::HalfedgeIter it = mesh.halfedges_begin(); it != mesh.halfedges_end(); ++it ) {
                if( to_vertex_handle( *it ) == vhandle[3] &&
                    from_vertex_handle( *it ) == vhandle[2] ) {
                        // Collapse edge
                        mesh.collapse( *it );
                        break;
                }
        }
*/      return 0;
}

