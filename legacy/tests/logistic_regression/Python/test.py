import csv
import numpy as np
import matplotlib.pyplot as plt
 
def logistic_func(beta, X, printme=False):
    '''
    logistic(sigmoid) function
    '''
    temp = 1.0/(1 + np.exp(-np.dot(X, beta.T)))

    if (printme):
        minus_npdot = -np.dot(X, beta.T)
        npexponent  =  np.exp(-np.dot(X, beta.T))
        print("         minus_npdot:",minus_npdot)
        print("         npexponent:",npexponent)
        print("         logistic result:",temp)

    return temp    
 
 
def log_gradient(beta, X, y):
    '''
    logistic gradient function
    '''
    first_calc = logistic_func(beta, X) - y.reshape(X.shape[0], -1)
    final_calc = np.dot(first_calc.T, X)
    return final_calc
 
 
def cost_func(beta, X, y):
    '''
    cost function, J
    '''
    log_func_v = logistic_func(beta, X)
    y = np.squeeze(y)
    
    step1 = y * np.log(log_func_v)
    step2 = (1 - y) * np.log(1 - log_func_v)
    final = -step1 - step2
    '''
        print("Y") 
        print(y)
        print("np.log(log_func_v)") 
        print(log_func_v)
        print("step1") 
        print(step1) 
        print("step2") 
        print(step2) 
        print("final") 
        print(final) 
    '''
    return np.mean(final)
 
 
def grad_desc(X, y, beta, lr=.0001, converge_change=.0001):
    '''
    gradient descent function
    '''
    cost = cost_func(beta, X, y)
    change_cost = 1
    num_iter = 1
     
    while(change_cost > converge_change):
        old_cost = cost 
        beta = beta - (lr * log_gradient(beta, X, y))
        cost = cost_func(beta, X, y)
        change_cost = old_cost - cost
        num_iter += 1

#        print("COST")
#        print(cost)
#        print("BETA")
#        print(beta)     
#        print(num_iter)     
    
    return beta, num_iter 
 
 
def pred_values(beta, X):
    '''
    function to predict labels
    '''

    pred_prob  = np.zeros((np.shape(X)[0]))
    pred_value = np.zeros((np.shape(X)[0]))
    for i in range(0,np.shape(X)[0]) :
        print("   Beta:", beta)
        print("   X:",   X[i] )
        pred_prob [i] = logistic_func(beta, X[i],True)
        pred_value[i] = np.where(pred_prob[i] >= .5, 1, 0)
        print("   pred_prob:", pred_prob[i])
        print("   pred_value:", pred_value[i])
        print("")

    return np.squeeze(pred_value)
 
 
def plot_reg(X, y, beta):
    '''
    function to plot decision boundary
    '''
    # labelled observations
    x_0 = X[np.where(y == 0.0)]
    x_1 = X[np.where(y == 1.0)]
     
    # plotting points with diff color for diff label
    plt.scatter(x_0[:, 1], x_0[:, 2], c='b', label='y = 0')
    plt.scatter(x_1[:, 1], x_1[:, 2], c='r', label='y = 1')
     
    # plotting decision boundary
    x1 = np.arange(0, 1, 0.1)
    x2 = -(beta[0,0] + beta[0,1]*x1)/beta[0,2]
    plt.plot(x1, x2, c='k', label='reg line')
 
    plt.xlabel('x1')
    plt.ylabel('x2')
    plt.legend()
    plt.show()
 
# formatting data
# --------------------------------------------------------- #
def loadCSV(filename):
    '''
    function to load dataset
    '''
    with open(filename,"r") as csvfile:
        lines = csv.reader(csvfile)
        dataset = list(lines)
        for i in range(len(dataset)):
            dataset[i] = [float(x) for x in dataset[i]]     
    return np.array(dataset).T
 
def normalize(X):
    '''
    function to normalize feature matrix, X
    '''
    # ORIGINAL NORMALIZATION
    # ----------------------
    # mins = np.min(X, axis = 0)
    # maxs = np.max(X, axis = 0)
    # rng = maxs - mins
    # norm_X = 1 - ((maxs - X)/rng)
    norm_X = X / 1024
    return norm_X
 # --------------------------------------------------------- #

def check_accurate_predictions (filename,beta):
    '''
    function to check if the prediction matrix results in
    the correct predictions for a separate dataset
    '''
    dataset = loadCSV(filename)
    X = normalize(dataset[:, :-1])
    X = np.hstack((np.matrix(np.ones(X.shape[0])).T, X))
    y = dataset[:, -1]
    y_pred = pred_values(beta, X)
    print("Correctly predicted labels:", np.sum(y == y_pred))

if __name__ == "__main__":
    # load the dataset
    dataset = loadCSV('./data/dataset1_red.csv')
    
    # normalizing feature matrix
    X = normalize(dataset[:, :-1])
    
    # stacking columns wth all ones in feature matrix
    X = np.hstack((np.matrix(np.ones(X.shape[0])).T, X))
    
    # response vector
    y = dataset[:, -1]
 
    # initial beta values
    beta = np.matrix(np.zeros(X.shape[1]))
 
    # beta values after running gradient descent
    beta, num_iter = grad_desc(X, y, beta)
 
    # estimated beta values and number of iterations
    print("Estimated regression coefficients:", beta)
    print("No. of iterations:", num_iter)

    check_accurate_predictions ('./data/dataset1_red.csv',beta)
'''
    check_accurate_predictions ('./data/dataset2_red.csv',beta)
    check_accurate_predictions ('./data/dataset3_red.csv',beta)
    check_accurate_predictions ('./data/dataset4_red.csv',beta)
    check_accurate_predictions ('./data/dataset5_red.csv',beta)
    check_accurate_predictions ('./data/dataset6_red.csv',beta)
    check_accurate_predictions ('./data/dataset7_red.csv',beta)
'''
    # predicted labels
    #y_pred = pred_values(beta, X)
     
    # number of correctly predicted labels
    #print("Correctly predicted labels:", np.sum(y == y_pred))

    # plotting regression line
    # plot_reg(X, y, beta)

