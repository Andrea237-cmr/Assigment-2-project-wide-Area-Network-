// scratch/wan-cloud.cc
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("WanCloudSimulation");

int main (int argc, char *argv[])
{
  // Activer l'affichage des logs pour voir les paquets
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  std::cout << "=== Simulation WAN + Cloud ===" << std::endl;
  std::cout << "Lancement de la simulation..." << std::endl;

  // Création des nœuds : Client et Serveur Cloud
  NodeContainer nodes;
  nodes.Create (2);
  std::cout << "✅ Création de 2 nœuds :" << std::endl;
  std::cout << "   - Nœud 0 : Client local" << std::endl;
  std::cout << "   - Nœud 1 : Serveur Cloud" << std::endl;

  // Configuration de la liaison WAN
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("5ms"));
  std::cout << "✅ Configuration WAN :" << std::endl;
  std::cout << "   - Débit : 10 Mbps" << std::endl;
  std::cout << "   - Latence : 5 ms" << std::endl;

  NetDeviceContainer devices = p2p.Install (nodes);

  // Installation de la pile Internet (TCP/IP)
  InternetStackHelper stack;
  stack.Install (nodes);

  // Attribution des adresses IP
  Ipv4AddressHelper address;
  address.SetBase ("192.168.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (devices);
  std::cout << "✅ Configuration réseau :" << std::endl;
  std::cout << "   - Client : " << interfaces.GetAddress(0) << std::endl;
  std::cout << "   - Cloud  : " << interfaces.GetAddress(1) << std::endl;

  // Serveur Cloud (écoute sur le port 9)
  UdpEchoServerHelper server (9);
  ApplicationContainer serverApps = server.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));
  std::cout << "✅ Serveur Cloud démarré (port 9)" << std::endl;

  // Client
  UdpEchoClientHelper client (interfaces.GetAddress (1), 9);
  client.SetAttribute ("MaxPackets", UintegerValue (5));
  client.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  client.SetAttribute ("PacketSize", UintegerValue (1024));
  std::cout << "✅ Client configuré :" << std::endl;
  std::cout << "   - 5 paquets de 1024 octets" << std::endl;
  std::cout << "   - Intervalle : 1 seconde" << std::endl;

  ApplicationContainer clientApps = client.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  std::cout << "\n🚀 Début de la simulation...\n" << std::endl;

  // Exécution de la simulation
  Simulator::Run ();
  Simulator::Destroy ();

  std::cout << "\n✅ Simulation terminée avec succès !" << std::endl;
  std::cout << "=== Fin de la simulation WAN + Cloud ===" << std::endl;

  return 0;
}
