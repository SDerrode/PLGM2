function [err, m_err] = compute_errors( hx, x )

	l = min( size(hx)(1), size(x)(1) );
	s = min( size(hx)(2), size(x)(2) );

	err = (hx( 1:l, 1:s) - x( 1:l, 1:s)).^2;
	m_err = sum( err, 1 ) / l;


end
