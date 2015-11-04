#include "CommunityDetection.h"
#include "ClusteringEvaluation.h"

#define ANALYSIS_MODE "-A"
#define EVALUATION_MODE "-E"
#define ANALYSIS_MODE_ARGUEMENT_NUMBER 7
#define EVALUATION_MODE_ARGUEMENT_NUMBER 6
#define SUPERVISED "S"
#define UNSUPERVISED "US"

int main(int argc, char* argv[])
{
    if (strcmp(argv[1], ANALYSIS_MODE) == 0)
    {
        if (argc != ANALYSIS_MODE_ARGUEMENT_NUMBER)
        {
            cout << "The number of argument is not correct." << endl;
            exit(1);
        }

        double dThreshold = atof(argv[2]);
        bool bIsWeighted = atoi(argv[3]) == 0 ? false : true;
        string strInputFileName(argv[4]);
        string strOutputCommunitiesFileName(argv[5]);
        string strOutputEdgesFileName(argv[6]);

        CommunityDetection communityDetection(bIsWeighted, dThreshold);
        communityDetection.Execute(strInputFileName);
        communityDetection.OutputCommunities(strOutputCommunitiesFileName);
        communityDetection.OutputEdges(strOutputEdgesFileName);
    }
    else if (strcmp(argv[1], EVALUATION_MODE) == 0)
    {
        if (argc != EVALUATION_MODE_ARGUEMENT_NUMBER)
        {
            cout << "The number of argument is not correct." << endl;
            exit(0);
        }

        if (strcmp(argv[2], SUPERVISED) == 0)
        {
            string strTargetFileName(argv[3]);
            string strGroundTruthFileName(argv[4]);
            string strResultFileName(argv[5]);

            map<int, set<int>*>* pTargetCommunities = ClusteringEvaluation::GenerateCommunities(strTargetFileName);
            map<int, set<int>*>* pGroundTruth = ClusteringEvaluation::GenerateCommunities(strGroundTruthFileName);
            double dInversePurity = ClusteringEvaluation::InversePurity(pTargetCommunities, pGroundTruth);
            double dSimplyPurity = ClusteringEvaluation::SimplyPurity(pTargetCommunities, pGroundTruth);
            double dNMI = ClusteringEvaluation::NMI(pTargetCommunities, pGroundTruth);
            double dRI = ClusteringEvaluation::RI(pTargetCommunities, pGroundTruth);
            double dARI = ClusteringEvaluation::ARI(pTargetCommunities, pGroundTruth);

            map<string, double> dictEvaluationResult;
            dictEvaluationResult["InvPur"] = dInversePurity;
            dictEvaluationResult["SimPur"] = dSimplyPurity;
            dictEvaluationResult["NMI"] = dNMI;
            dictEvaluationResult["RI"] = dRI;
            dictEvaluationResult["ARI"] = dARI;
            Helper::OutputEvaluationResult(strResultFileName, dictEvaluationResult);

            ClusteringEvaluation::ClearResources(pTargetCommunities);
            ClusteringEvaluation::ClearResources(pGroundTruth);
        }
        else if (strcmp(argv[2], UNSUPERVISED) == 0)
        {
            string strTargetFileName(argv[3]);
            string strGraphFileName(argv[4]);
            string strResultFileName(argv[5]);

            map<int, set<int>*>* pTargetCommunities = ClusteringEvaluation::GenerateCommunities(strTargetFileName);
            map<int, set<int>*>* pGraph = ClusteringEvaluation::GenerateAdjecentList(strGraphFileName);
            double dModurility = ClusteringEvaluation::Modularity(pTargetCommunities, pGraph);
            double dNcut = ClusteringEvaluation::Ncut(pTargetCommunities, pGraph);


            map<string, double> dictEvaluationResult;
            dictEvaluationResult["Mod"] = dModurility;
            dictEvaluationResult["Ncut"] = dNcut;
            Helper::OutputEvaluationResult(strResultFileName, dictEvaluationResult);

            ClusteringEvaluation::ClearResources(pTargetCommunities);
            ClusteringEvaluation::ClearResources(pGraph);
        }
        else
        {
            cout << "The evaluation mode '" << argv[2] << "' does not exist." << endl;
            exit(1);
        }
    }
    else
    {
        cout << "The execution mode '" << argv[1] << "' does not exist." << endl;
    }

    return 0;
}

/*
int main()
{
    const string fileName = "C:\\Users\\ssunah\\gitchina\\Community-Detection\\dataset\\small\\polbooks\\polbooks_edges_input.csv";
    map<int, set<int>* >* pAdjacentList = ClusteringEvaluation::GenerateAdjecentList(fileName);
    double dCC = ClusteringEvaluation::LocalClusteringCoefficient(pAdjacentList);
    cout << dCC << endl;
    ClusteringEvaluation::ClearResources(pAdjacentList);
    return 0;
}
<<<<<<< HEAD
*/

