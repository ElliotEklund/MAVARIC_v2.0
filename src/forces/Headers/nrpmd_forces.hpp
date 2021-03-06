#ifndef nrpmd_forces_hpp
#define nrpmd_forces_hpp

#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include "dSpring_dQ.hpp"
#include "dStateIndep_dQ.hpp"
#include "StateDepPots.h"

using namespace boost::numeric::ublas;

class nrpmd_forces{
    
public:
    nrpmd_forces(int nuc_beads,int elec_beads, int num_states,
                        double mass, double beta_nuc_beads);
    
    /*
     Update dHdP to reflect the state of P
     P: vector of bead momentum
     */
    void update_dHdP(const vector<double> &P);
    
    /*
     Update dHdQ to reflect the state of Q,x,p
     Q: vector of bead positions
     x: matrix of x mapping variables
     p: matrix of p mapping variables
     */
    void update_dHdQ(const vector<double> &Q, const matrix<double> &x,
                        const matrix<double> &p);
    /*
     Update dHdx to reflect the state of Q,x,p
     Q: vector of bead positions
     x: matrix of x mapping variables
     p: matrix of p mapping variables
     */
    void update_dHdx(const vector<double> &Q, const matrix<double> &x,
                        const matrix<double> &p);
    /*
     Update dHdp to reflect the state of Q,x,p
     Q: vector of bead positions
     x: matrix of x mapping variables
     p: matrix of p mapping variables
     */
    void update_dHdp(const vector<double> &Q, const matrix<double> &x,
                        const matrix<double> &p);

    /* Update state of dHdP, dHdQ, dHdx, and dHdp.*/
    void update_Forces(const vector<double> &Q,const vector<double> &P,
                       const matrix<double> &x,const matrix<double> &p);
    
/* Mutators */
    /* Return dHdQ*/
    const vector<double> & get_dHdQ();
  
    /* Return dHdP*/
    const vector<double> & get_dHdP();
   
    /* Return dHdx*/
    const matrix<double> & get_dHdx();

    /* Return dHdp*/
    const matrix<double> & get_dHdp();
    

/* Debugging*/
    void print_dHdQ(); 
    void print_dHdP(); 
    void print_dHdx(); 
    void print_dHdp(); 
    
private:
    
/* Data */
    double ONE_mass; //1.0/mass
    double beta_nuc_beads; //beta/nuc_beads
    double ONE_beta_nuc_beads; //1.0/beta_nuc_beads
    double TWO_beta_nuc_beads; //2.0/beta_nuc_beads
    int nuc_beads; //number of nuclear beads
    int elec_beads; //number of electronic beads
    int num_states; //number of electronic states

    vector<double> dHdQ, dHdP; //derivative of Hamiltonian wrt Q,P
    matrix<double> dHdx, dHdp; //derivative of Hamiltonian wrt x,p

    vector<double> dVspring_dQ_vec;
    vector<double> dV0_dQ_vec;
    
/* Objects */
    dSpring_dQ dVspring_dQ;
    dStateIndep_dQ dV0_dQ;
    StateDepPots Vdep;
};

#endif
