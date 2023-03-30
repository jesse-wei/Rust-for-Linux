#include<linux/module.h>
#include<linux/kernel.h>

#define DRV_NAME "e1000"

#define INTEL_E1000_ETHERNET_DEVICE(device_id) {\
	PCI_DEVICE(PCI_VENDOR_ID_INTEL, device_id)}


struct e1000_adapter {
	unsigned long active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	u16 mng_vlan_id;
	u32 bd_number;
	u32 rx_buffer_len;
	u32 wol;
	u32 smartspeed;
	u32 en_mng_pt;
	u16 link_speed;
	u16 link_duplex;
	spinlock_t stats_lock;
	unsigned int total_tx_bytes;
	unsigned int total_tx_packets;
	unsigned int total_rx_bytes;
	unsigned int total_rx_packets;
	/* Interrupt Throttle Rate */
	u32 itr;
	u32 itr_setting;
	u16 tx_itr;
	u16 rx_itr;

	u8 fc_autoneg;

	/* TX */
	struct e1000_tx_ring *tx_ring;      /* One per active queue */
	unsigned int restart_queue;
	u32 txd_cmd;
	u32 tx_int_delay;
	u32 tx_abs_int_delay;
	u32 gotcl;
	u64 gotcl_old;
	u64 tpt_old;
	u64 colc_old;
	u32 tx_timeout_count;
	u32 tx_fifo_head;
	u32 tx_head_addr;
	u32 tx_fifo_size;
	u8  tx_timeout_factor;
	atomic_t tx_fifo_stall;
	bool pcix_82544;
	bool detect_tx_hung;
	bool dump_buffers;

	/* RX */
	bool (*clean_rx)(struct e1000_adapter *adapter,
			 struct e1000_rx_ring *rx_ring,
			 int *work_done, int work_to_do);
	void (*alloc_rx_buf)(struct e1000_adapter *adapter,
			     struct e1000_rx_ring *rx_ring,
			     int cleaned_count);
	struct e1000_rx_ring *rx_ring;      /* One per active queue */
	struct napi_struct napi;

	int num_tx_queues;
	int num_rx_queues;

	u64 hw_csum_err;
	u64 hw_csum_good;
	u32 alloc_rx_buff_failed;
	u32 rx_int_delay;
	u32 rx_abs_int_delay;
	bool rx_csum;
	u32 gorcl;
	u64 gorcl_old;

	/* OS defined structs */
	struct net_device *netdev;
	struct pci_dev *pdev;

	/* structs defined in e1000_hw.h */
	struct e1000_hw hw;
	struct e1000_hw_stats stats;
	struct e1000_phy_info phy_info;
	struct e1000_phy_stats phy_stats;

	u32 test_icr;
	struct e1000_tx_ring test_tx_ring;
	struct e1000_rx_ring test_rx_ring;

	int msg_enable;

	/* to not mess up cache alignment, always add to the bottom */
	bool tso_force;
	bool smart_power_down;	/* phy smart power down */
	bool quad_port_a;
	unsigned long flags;
	u32 eeprom_wol;

	/* for ioport free */
	int bars;
	int need_ioport;

	bool discarding;

	struct work_struct reset_task;
	struct delayed_work watchdog_task;
	struct delayed_work fifo_stall_task;
	struct delayed_work phy_info_task;
};


static int e1000__open(struct net_device *netdev);


static int e1000_close(struct net_device *netdev);


static netdev_tx_t e1000_start_xmit(struct sk_buff *skb, struct net_device *netdev);


static void e1000_tx_timeout(struct net_device *netdev, unsigned int txqueue)


static int e1000_probe(struct pci_dev *pdev, const struct pci_device_id *ent);


static void e1000_remove(struct pci_dev *pdev);


static void e1000_shutdown(struct pci_dev *pdev);