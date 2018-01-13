#include "tkalman_f_estimation_t1_block_estimator.hpp"
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include "gsl_triangle_matrix.hpp"
tkalman :: f_estimation :: t1_block ::estimator :: estimator()
{
	initialize();
}

tkalman :: f_estimation :: t1_block :: estimator :: estimator( const tkalman :: f_estimation :: t1_block :: parameters * params ) throw ( exception &)
{
	initialize();
	if ( setup ( params ) )
		throw ( invalid_argument( "Invalid argument(s) in t2_block :: t2_block!") );
}

void tkalman :: f_estimation :: t1_block ::estimator :: reset()
{
	free();
	initialize();
}

int tkalman :: f_estimation :: t1_block ::estimator :: setup (	const tkalman :: f_estimation :: t1_block :: parameters * params  )
{
	reset();
	if ( params == NULL )
		return 1;
	p = params;
	if ( p->size_g() == 0 )
		return 0;
	else
	{
		alloc();
	}
	return 0;
}

void tkalman :: f_estimation :: t1_block :: estimator ::  estimate(	gsl_matrix * f_i,
																	const gsl_matrix * sqrt_c_i_view_00,
																	const gsl_matrix * sqrt_c_i_view_01 ) const
{
	gsl_matrix_set_zero( f_i );
	//Rien à faire ici!
	if ( p->size_g() == 0 )
		return;
	
	//A. Calcul de sq(Di)
		//Construction de la matrice 
		// Mi^T	0
		// 0	I
		gsl_matrix_transpose_memcpy( 	w->mat_tpi_gpi_1_view_00(),
										p->m() );

		//Construction de la matrice 
		// [	sq(C)(0,0)	sq(C)(0,1)	]
		// [	0				0		]
		gsl_matrix_memcpy( 	w->mat_tpi_tpi_view_00(),  
							sqrt_c_i_view_00 );
							
		gsl_matrix_memcpy( 	w->mat_tpi_tpi_view_01(),  
							sqrt_c_i_view_01 );
							

		//Produit
		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						w->mat_tpi_tpi(),
						w->mat_tpi_gpi_1(),
						0.0,
						w->mat_tpi_gpi_2() );
		

		//Decomposition QR
		gsl_linalg_QR_decomp(	w->mat_tpi_gpi_2(),
								w->vect_gpi() );
		gsl_triangle_matrix(w->mat_tpi_gpi_2());
		

		
		
	//Calcul de inv(sq(Di(0,0)))
	    gsl_permutation_init(w->perm_g());
        gsl_linalg_LU_invert(	w->mat_tpi_gpi_2_view_00(), 
								w->perm_g(), 
								w->mat_gg() );
								

								
								
	//Calcul de G^t
		gsl_blas_dgemm(	CblasNoTrans,
						CblasNoTrans,
						1.0,
						w->mat_gg(),
						w->mat_tpi_gpi_2_view_01(),
						0.0,
						w->mat_gi() );
						

						
	//Calcul de F_i
		gsl_blas_dgemm( CblasTrans,
						CblasNoTrans,
						1.0,
						w->mat_gi(),
						p->m(),
						0.0,
						f_i );
		//~ gsl_matrix_fprintf_( stdout, API_DEFAULT_MATRIX_FORMAT, f_i );	
		//~ cout << endl;

}

tkalman :: f_estimation :: t1_block :: estimator :: ~estimator()
{
	reset();
}

void tkalman :: f_estimation :: t1_block :: estimator :: free()
{
	if (w)
		delete w;
}

void tkalman :: f_estimation :: t1_block :: estimator :: alloc()
{
	w = new tkalman :: f_estimation :: t1_block :: workspace( 	p->size_i(),
																p->size_t(), 
																p->size_g() );
}

void tkalman :: f_estimation :: t1_block :: estimator :: initialize()
{
	p = 0;
	w = 0;
}
